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

  ledInit();

  return true;
}