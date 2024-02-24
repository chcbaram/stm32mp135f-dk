#include "ap.h"
#include "lvgl/ui.h"
#include "widgets/lv_demo_widgets.h"


void apInit(void)
{
  #ifdef _USE_HW_CLI
  cliOpen(HW_UART_CH_CLI, 115200);
  cliLogo();
  #endif     

  lvglInit();
}

void apMain(void)
{
  uint32_t pre_time;


  // ui_init();
  lv_demo_widgets();

  pre_time = millis();
  while(1)
  {
    if (millis()-pre_time >= 500)
    {
      pre_time = millis();
      ledToggle(HW_LED_CH_LED_B);
    }

    #ifdef _USE_HW_CLI
    cliMain();
    #endif    

    lvglUpdate();
  }
}

