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
  logPrintf("\n");

  i2cInit();
  
  return true;
}