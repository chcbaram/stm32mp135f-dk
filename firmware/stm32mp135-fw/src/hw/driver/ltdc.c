#include "ltdc.h"


#ifdef _USE_HW_LTDC
#include "gpio.h"
#include "cli.h"


#define FRAME_BUF_ADDR        HW_LTDC_BUF_ADDR
#define FRAME_OSD_ADDR        (HW_LTDC_BUF_ADDR + (2048)*1024)
#define FRAME_BUF_CNT         2


#define LCD_WIDTH             HW_LCD_WIDTH      // LCD PIXEL WIDTH            
#define LCD_HEIGHT            HW_LCD_HEIGHT     // LCD PIXEL HEIGHT           


#define LCD_HSYNC             ((uint16_t)41)    // Horizontal synchronization 
#define LCD_HBP               ((uint16_t)13)    // Horizontal back porch      
#define LCD_HFP               ((uint16_t)32)    // Horizontal front porch     


#define LCD_VSYNC             ((uint16_t)10)    // Vertical synchronization   
#define LCD_VBP               ((uint16_t)2)     // Vertical back porch        
#define LCD_VFP               ((uint16_t)2)     // Vertical front porch       


#define FRAME_IMG_SIZE        (LCD_WIDTH * LCD_HEIGHT * 2)




void ltdcSetFrameBuffer(uint16_t* addr);
#ifdef _USE_HW_CLI
static void cliCmd(cli_args_t *args);
#endif



static LTDC_HandleTypeDef hltdc;
static bool is_init = false;
static bool ltdc_request_draw = false;

static uint16_t lcd_int_active_line;
static uint16_t lcd_int_porch_line;
static uint32_t frame_rate = 0;
static uint32_t frame_cnt = 0;
static uint32_t frame_time = 0;

static uint32_t draw_rate = 0;
static uint32_t draw_cnt = 0;

static uint32_t  frame_index = 0;
__attribute__((section(".sdram_buf"))) __attribute__((aligned(64)))
static uint16_t frame_mem[LCD_WIDTH*LCD_HEIGHT*2*2];

static uint16_t *frame_buffer[FRAME_BUF_CNT] =
    {
      (uint16_t *)&frame_mem[LCD_WIDTH*LCD_HEIGHT*2*0],
      (uint16_t *)&frame_mem[LCD_WIDTH*LCD_HEIGHT*2*1],
    };

uint16_t *ltdc_draw_buffer;
uint16_t *ltdc_osd_draw_buffer = (uint16_t *)FRAME_OSD_ADDR;

static bool is_double_buffer = true;
static void (*vsync_func)(uint8_t mode) = NULL;





bool ltdcInit(void)
{
  bool ret = true;


  hltdc.Instance = LTDC;

  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;

  hltdc.Init.HorizontalSync     = (LCD_HSYNC  - 1);
  hltdc.Init.VerticalSync       = (LCD_VSYNC  - 1);
  hltdc.Init.AccumulatedHBP     = (LCD_HSYNC  + LCD_HBP - 1);
  hltdc.Init.AccumulatedVBP     = (LCD_VSYNC  + LCD_VBP - 1);
  hltdc.Init.AccumulatedActiveH = (LCD_HEIGHT + LCD_VSYNC + LCD_VBP - 1);
  hltdc.Init.AccumulatedActiveW = (LCD_WIDTH  + LCD_HSYNC + LCD_HBP - 1);
  hltdc.Init.TotalHeigh         = (LCD_HEIGHT + LCD_VSYNC + LCD_VBP + LCD_VFP - 1);
  hltdc.Init.TotalWidth         = (LCD_WIDTH  + LCD_HSYNC + LCD_HBP + LCD_HFP - 1);

  hltdc.Init.Backcolor.Blue   = 0;
  hltdc.Init.Backcolor.Green  = 0;
  hltdc.Init.Backcolor.Red    = 0;
  
  if(HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    ret = false;
  }

  for (int ch=0; ch<FRAME_BUF_CNT; ch++)
  {
    for (int i=0; i<LCD_WIDTH*LCD_HEIGHT; i++)
    {
      frame_buffer[ch][i] = 0x0000;
    }
  }

  ltdcLayerInit(LTDC_LAYER_1, (uint32_t)frame_buffer[frame_index]);
  ltdcLayerInit(LTDC_LAYER_2, FRAME_OSD_ADDR);
  ltdcSetAlpha(LTDC_LAYER_2, 0);


  if (is_double_buffer == true)
  {
    ltdc_draw_buffer = frame_buffer[frame_index ^ 1];
  }
  else
  {
    ltdc_draw_buffer = frame_buffer[frame_index];
  }

  lcd_int_active_line = (LTDC->BPCR & 0x7FF) - (LCD_VBP/2);
  lcd_int_porch_line  = (LTDC->AWCR & 0x7FF) - 1;

  HAL_LTDC_ProgramLineEvent(&hltdc, lcd_int_active_line);
  __HAL_LTDC_ENABLE_IT(&hltdc, LTDC_IT_LI);

  /* Disable the FIFO underrun interrupt */
  __HAL_LTDC_DISABLE_IT(&hltdc, LTDC_IT_FU);


  IRQ_SetPriority(LTDC_IRQn, 5);
  IRQ_Enable(LTDC_IRQn);

  is_init = ret;
  logPrintf("[%s] ltdcInit()\n", is_init ? "OK":"NG");
  PLL4_ClocksTypeDef pll4_clock;
  HAL_RCC_GetPLL4ClockFreq(&pll4_clock);
  logPrintf("     freq : %d.%03d Mhz\n", 
    pll4_clock.PLL4_Q_Frequency/1000000,
    (pll4_clock.PLL4_Q_Frequency%1000000)/1000
    );

#ifdef _USE_HW_CLI
  cliAdd("ltdc", cliCmd);
#endif
  return ret;
}

bool ltdcSetVsyncFunc(void (*func)(uint8_t mode))
{
  vsync_func = func;
  return true;
}

void ltdcSetAlpha(uint16_t LayerIndex, uint32_t value)
{
  HAL_LTDC_SetAlpha(&hltdc, value, LayerIndex);
}


bool ltdcLayerInit(uint16_t LayerIndex, uint32_t Address)
{
  LTDC_LayerCfgTypeDef      pLayerCfg;
  bool ret = true;


  /* Layer1 Configuration ------------------------------------------------------*/

  /* Windowing configuration */
  /* In this case all the active display area is used to display a picture then :
     Horizontal start = horizontal synchronization + Horizontal back porch = 43
     Vertical start   = vertical synchronization + vertical back porch     = 12
     Horizontal stop = Horizontal start + window width -1 = 43 + 480 -1
     Vertical stop   = Vertical start + window height -1  = 12 + 272 -1      */
  if (LayerIndex == LTDC_LAYER_1)
  {
    pLayerCfg.WindowX0 = 0;
    pLayerCfg.WindowX1 = LCD_WIDTH;
    pLayerCfg.WindowY0 = 0;
    pLayerCfg.WindowY1 = LCD_HEIGHT;
  }
  else
  {
    pLayerCfg.WindowX0 = (LCD_WIDTH-200)/2;
    pLayerCfg.WindowX1 = pLayerCfg.WindowX0 + 200;
    pLayerCfg.WindowY0 = (LCD_HEIGHT-200)/2;
    pLayerCfg.WindowY1 = pLayerCfg.WindowY0 + 200;
  }


  /* Pixel Format configuration*/
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;

  /* Start Address configuration : frame buffer is located at FLASH memory */
  pLayerCfg.FBStartAdress = Address;

  /* Alpha constant (255 == totally opaque) */
  pLayerCfg.Alpha = 255;

  /* Default Color configuration (configure A,R,G,B component values) : no background color */
  pLayerCfg.Alpha0          = 0; /* fully transparent */
  pLayerCfg.Backcolor.Blue  = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red   = 0;

  /* Configure blending factors */
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;

  /* Configure the number of lines and number of pixels per line */
  pLayerCfg.ImageWidth  = LCD_WIDTH;
  pLayerCfg.ImageHeight = LCD_HEIGHT;

  pLayerCfg.HorMirrorEn = false;
  pLayerCfg.VertMirrorEn = false;

  /* Configure the Layer*/
  if(HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, LayerIndex) != HAL_OK)
  {
    /* Initialization Error */
    ret = false;
  }


  return ret;
}


void ltdcSetFrameBuffer(uint16_t* addr)
{
  // LTDC_Layer1->CFBAR = (uint32_t)addr;

  // /* Reload immediate */
  // LTDC->SRCR = (uint32_t)LTDC_SRCR_IMR;  
  HAL_LTDC_SetAddress(&hltdc, (uint32_t)addr, LTDC_LAYER_1);
}


int32_t ltdcWidth(void)
{
  return LCD_WIDTH;
}

int32_t ltdcHeight(void)
{
  return LCD_HEIGHT;
}

uint32_t ltdcGetBufferAddr(uint8_t index)
{
  return  (uint32_t)frame_buffer[frame_index];
}

bool ltdcDrawAvailable(void)
{
  return !ltdc_request_draw;
}

void ltdcRequestDraw(void)
{
  ltdc_request_draw = true;
}

void ltdcSetDoubleBuffer(bool enable)
{
  is_double_buffer = enable;

  if (enable == true)
  {
    ltdc_draw_buffer = frame_buffer[frame_index^1];
  }
  else
  {
    ltdc_draw_buffer = frame_buffer[frame_index];
  }
}

bool ltdcGetDoubleBuffer(void)
{
  return is_double_buffer;
}

uint16_t *ltdcGetFrameBuffer(void)
{
  return  ltdc_draw_buffer;
}

uint16_t *ltdcGetCurrentFrameBuffer(void)
{
  return  frame_buffer[frame_index];
}


void ltdcSwapFrameBuffer(void)
{
  if (ltdc_request_draw == true)
  {
    frame_index ^= 1;
    draw_cnt++;

    ltdcSetFrameBuffer(frame_buffer[frame_index]);

    if (is_double_buffer == true)
    {
      ltdc_draw_buffer = frame_buffer[frame_index ^ 1];
    }
    else
    {
      ltdc_draw_buffer = frame_buffer[frame_index];
    }
    ltdc_request_draw = false;
  }
}

uint32_t ltdcGetFrameRate(void)
{
  return frame_rate;
}

uint32_t ltdcGetDrawRate(void)
{
  return draw_rate;
}

void LTDC_IRQHandler(void)
{
  HAL_LTDC_IRQHandler(&hltdc);
}

void HAL_LTDC_LineEventCallback(LTDC_HandleTypeDef* hltdc)
{
  if (LTDC->LIPCR == lcd_int_active_line)
  {
    ltdcSwapFrameBuffer();
    HAL_LTDC_ProgramLineEvent(hltdc, lcd_int_active_line);

    if (vsync_func != NULL)
    {
      vsync_func(0);
    }
    frame_cnt++;
    if (millis()-frame_time >= 1000)
    {
      frame_time = millis();
      frame_rate = frame_cnt;
      frame_cnt = 0;

      draw_rate = draw_cnt;
      draw_cnt = 0;
    }
  }
  else
  {
    HAL_LTDC_ProgramLineEvent(hltdc, lcd_int_active_line);
    if (vsync_func != NULL)
    {
      vsync_func(1);
    }    
  }
}



void HAL_LTDC_MspInit(LTDC_HandleTypeDef* ltdcHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(ltdcHandle->Instance==LTDC)
  {
    RCC_OscInitTypeDef init;

    HAL_RCC_GetOscConfig(&init);

    init.PLL4.PLLQ = 65; // 60
    RCCEx_PLL4_Config(&init.PLL4);

    /* LTDC clock enable */
    __HAL_RCC_LTDC_CLK_ENABLE();

    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**LTDC GPIO Configuration
    PE13     ------> LTDC_R6
    PG0     ------> LTDC_G5
    PG7     ------> LTDC_R2
    PH13     ------> LTDC_G2
    PF3     ------> LTDC_G3
    PF5     ------> LTDC_R5
    PA15     ------> LTDC_G7
    PE0     ------> LTDC_B5
    PE9     ------> LTDC_R7
    PH14     ------> LTDC_B4
    PG4     ------> LTDC_VSYNC
    PF1     ------> LTDC_B7
    PC6     ------> LTDC_HSYNC
    PB6     ------> LTDC_B6
    PD14     ------> LTDC_R4
    PD5     ------> LTDC_G4
    PD9     ------> LTDC_CLK
    PH9     ------> LTDC_DE
    PC7     ------> LTDC_G6
    PD10     ------> LTDC_B2
    PF2     ------> LTDC_B3
    PB10     ------> LTDC_R3
    */
    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_0|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LCD;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LCD;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LCD;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LCD;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF11_LCD;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF11_LCD;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF11_LCD;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF13_LCD;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LCD;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_LCD;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LCD;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LCD;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF13_LCD;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LCD;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LCD;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Enable LTDC reset state */
    __HAL_RCC_LTDC_FORCE_RESET();

    /* Release LTDC from reset state */
    __HAL_RCC_LTDC_RELEASE_RESET();
  }
}

void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef *hltdc)
{
  if(hltdc->Instance==LTDC)
  {
    /* Peripheral clock disable */
    __HAL_RCC_LTDC_CLK_DISABLE();

    /**LTDC GPIO Configuration
    PE13     ------> LTDC_R6
    PG0     ------> LTDC_G5
    PG7     ------> LTDC_R2
    PH13     ------> LTDC_G2
    PF3     ------> LTDC_G3
    PF5     ------> LTDC_R5
    PA15     ------> LTDC_G7
    PE0     ------> LTDC_B5
    PE9     ------> LTDC_R7
    PH14     ------> LTDC_B4
    PG4     ------> LTDC_VSYNC
    PF1     ------> LTDC_B7
    PC6     ------> LTDC_HSYNC
    PB6     ------> LTDC_B6
    PD14     ------> LTDC_R4
    PD5     ------> LTDC_G4
    PD9     ------> LTDC_CLK
    PH9     ------> LTDC_DE
    PC7     ------> LTDC_G6
    PD10     ------> LTDC_B2
    PF2     ------> LTDC_B3
    PB10     ------> LTDC_R3
    */
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_13|GPIO_PIN_0|GPIO_PIN_9);

    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_0|GPIO_PIN_7|GPIO_PIN_4);

    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_9);

    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_1|GPIO_PIN_2);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_15);

    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6|GPIO_PIN_7);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6|GPIO_PIN_10);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_14|GPIO_PIN_5|GPIO_PIN_9|GPIO_PIN_10);
  }
}


#ifdef _USE_HW_CLI
void cliCmd(cli_args_t *args)
{
  bool ret = false;


  if (args->argc == 1 && args->isStr(0, "info") == true)
  {
    cliPrintf("is_init    : %s\n", is_init ? "True":"False");
    cliPrintf("buf addr 0 : 0x%X\n", (uint32_t)frame_buffer[0]);
    cliPrintf("         1 : 0x%X\n", (uint32_t)frame_buffer[1]);
    cliPrintf("frame rate : %d fps\n", frame_rate);
    cliPrintf("int active : %d \n", lcd_int_active_line);
    cliPrintf("int porch  : %d \n", lcd_int_porch_line);
    ret = true;
  }

  if (args->argc == 1 && args->isStr(0, "test") == true)
  {
    uint32_t pre_time;
    uint16_t color_tbl[] = {0xF800, 0x07E0, 0x001F};
    uint16_t color_index = 0;


    pre_time = millis();
    while(cliKeepLoop())
    {
      if (ltdcDrawAvailable() && millis()-pre_time >= 500)
      {
        pre_time = millis();
        
        uint16_t *p_buf;
        uint32_t pre_time_draw = millis();
        uint32_t exe_time;
        uint16_t color;

        p_buf = ltdcGetFrameBuffer();
        color = color_tbl[color_index];
        for (int i=0; i<LCD_WIDTH*LCD_HEIGHT; i++)
        {
          p_buf[i] = color;
        }
        exe_time = millis()-pre_time_draw;
        
        ltdcRequestDraw();

        cliPrintf("%d ms, color 0x%04X\n", exe_time, color);

        color_index = (color_index + 1) % (sizeof(color_tbl)/sizeof(uint16_t));
      }
    }
    ret = true;
  }

  if (ret != true)
  {
    cliPrintf("ltdc info\n");
    cliPrintf("ltdc test\n");
  }
}
#endif

#endif