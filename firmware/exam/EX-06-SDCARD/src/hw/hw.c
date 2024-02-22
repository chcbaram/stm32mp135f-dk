#include "hw.h"




extern uint32_t _fw_flash_begin;
extern uint32_t _fw_size;
extern uint32_t _free_ram;

volatile const firm_ver_t firm_ver __attribute__((section(".version"))) = 
{
  .magic_number = VERSION_MAGIC_NUMBER,
  .version_str  = _DEF_FIRMWATRE_VERSION,
  .name_str     = _DEF_BOARD_NAME,
  .firm_addr    = (uint32_t)&_fw_flash_begin
};





bool hwInit(void)
{  
  bspInit();

  clocksInit();
  
  #ifdef _USE_HW_CLI
  cliInit();
  #endif
  logInit();
  ledInit();
  uartInit();
  for (int i=0; i<UART_MAX_CH; i++)
  {
    uartOpen(i, 115200);
  }

  logOpen(HW_LOG_CH, 115200);
  logPrintf("\r\n[ Firmware Begin... ]\r\n");
  logPrintf("Name      \t: %s\r\n", _DEF_BOARD_NAME);
  logPrintf("Ver       \t: %s\r\n", _DEF_FIRMWATRE_VERSION);  
  logPrintf("CPU  Clock\t: %d Mhz\r\n", (int)HAL_RCC_GetMPUSSFreq()/1000000);
  logPrintf("PCLK1     \t: %d Mhz\r\n", (int)HAL_RCC_GetPCLK1Freq()/1000000);
  logPrintf("PCLK2     \t: %d Mhz\r\n", (int)HAL_RCC_GetPCLK2Freq()/1000000);
  logPrintf("PCLK5     \t: %d Mhz\r\n", (int)HAL_RCC_GetPCLK5Freq()/1000000);
  logPrintf("PCLK6     \t: %d Mhz\r\n", (int)HAL_RCC_GetPCLK6Freq()/1000000);

  PLL2_ClocksTypeDef pll2_clocks;
  PLL3_ClocksTypeDef pll3_clocks;
  PLL4_ClocksTypeDef pll4_clocks;

  HAL_RCC_GetPLL2ClockFreq(&pll2_clocks);
  HAL_RCC_GetPLL3ClockFreq(&pll3_clocks);
  HAL_RCC_GetPLL4ClockFreq(&pll4_clocks);
  logPrintf("PLL2_P    \t: %d Mhz\r\n", (int)pll2_clocks.PLL2_P_Frequency/1000000);
  logPrintf("PLL2_R(DDR)\t: %d Mhz\r\n", (int)pll2_clocks.PLL2_R_Frequency/1000000);
  logPrintf("PLL3_Q    \t: %d Mhz\r\n", (int)pll3_clocks.PLL3_Q_Frequency/1000000);
  logPrintf("PLL4_P(SD)\t: %d Mhz\r\n", (int)pll4_clocks.PLL4_P_Frequency/1000000);
  logPrintf("PLL4_Q    \t: %d Mhz\r\n", (int)pll4_clocks.PLL4_Q_Frequency/1000000);


  logPrintf("\n");

  i2cInit();
  pmicInit();
  ddrInit();
  gpioInit();
  sdInit();
  
  return true;
}