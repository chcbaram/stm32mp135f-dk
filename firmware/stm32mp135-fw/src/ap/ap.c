#include "ap.h"




void apInit(void)
{  
}

void apMain(void)
{
  uint32_t pre_time;

  pre_time = millis();
  while(1)
  {
    if (millis()-pre_time >= 500)
    {
      pre_time = millis();
      ledToggle(HW_LED_CH_LED);
    }
  }
}

