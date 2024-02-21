#include "ddr.h"



#ifdef _USE_HW_DDR
#include "cli.h"
#include "pmic.h"


#if CLI_USE(HW_DDR)
static void cliCmd(cli_args_t *args);
#endif

static bool ddrInitSetup(void);

static DDR_InitTypeDef hddr;

static bool is_init = false;
static bool is_setup = false;


bool ddrInit(void)
{
  bool ret = true;


  is_setup = HW_DDR_SETUP;

  logPrintf("[%s] ddrInit()\n", ret ? "OK":"NG");
  if (ret == true)
  {
    if (is_setup)
    {
      ret = ddrInitSetup();
      logPrintf("[%s] ddrInitSetup()\n", ret ? "OK":"NG");
    }

    logPrintf("     ddr addr : 0x%X\n", HW_DDR_ADDR);
    logPrintf("     ddr size : %d MB\n", HW_DDR_SIZE/1024/1024);
  }

  is_init = ret;

#if CLI_USE(HW_DDR)
  cliAdd("ddr", cliCmd);
#endif
  return ret;
}

bool ddrInitSetup(void)
{
  bool ret = true;


  pmicEnableDDR();

  hddr.wakeup_from_standby = false;
  hddr.self_refresh        = false;
  hddr.zdata               = 0;
  hddr.clear_bkp           = false;
  if (HAL_DDR_Init(&hddr) != HAL_OK)
  {
    ret = false;
  }

  return ret;
}

#if CLI_USE(HW_DDR)
void cliCmd(cli_args_t *args)
{
  bool ret = false;


  if (args->argc == 1 && args->isStr(0, "info"))
  {
    cliPrintf("is_init     : %s\n", is_init ? "True":"False");
    cliPrintf("is_setup    : %s\n", is_setup ? "True":"False");
    cliPrintf("ddr addr    : 0x%X\n", HW_DDR_ADDR);
    cliPrintf("ddr size    : %d MB\n", HW_DDR_SIZE/1024/1024);    
    ret = true;
  }

  if (args->argc >= 2 && args->isStr(0, "test"))
  {
    uint32_t addr = HW_DDR_ADDR;
    uint32_t length;
    uint32_t pre_time;
    uint32_t exe_time_read;
    uint32_t exe_time_write;

    if (args->argc == 3)
    {
      addr   = (uint32_t)args->getData(1);
      length = (uint32_t)args->getData(2);
    }
    else 
    {
      length = (uint32_t)args->getData(1);
    }

    cliPrintf("addr   : 0x%X\n", addr);
    cliPrintf("length : %d MB\n", length);

    if (addr >= HW_DDR_ADDR && (addr + length*1024*1024) <= (HW_DDR_ADDR + HW_DDR_SIZE))
    {
      bool is_ok = true;
      uint32_t *p_data = (uint32_t *)addr;

      pre_time = millis();
      for (int i=0; i<length*1024*1024/4; i++)
      {
        p_data[i] = i;
      }
      exe_time_write = millis()-pre_time;

      volatile uint32_t read_data;

      pre_time = millis();
      for (int i=0; i<length*1024*1024/4; i++)
      {
        read_data = p_data[i];
      }
      (void)read_data;
      exe_time_read = millis()-pre_time;

      for (int i=0; i<length*1024*1024/4; i++)
      {
        if (p_data[i] != i)
        {
          is_ok = false;
          cliPrintf("err 0x%X \n", i*4);
          break;
        }
      }

      cliPrintf("read  %d ms\n", exe_time_read);
      cliPrintf("write %d ms\n", exe_time_write);
      cliPrintf("read  %d MB/s\n", length * 1000 / exe_time_read);
      cliPrintf("write %d MB/s\n", length * 1000 / exe_time_write);
      cliPrintf("%s\n", is_ok ? "OK":"Fail");
    }
    ret = true;
  }

  if (ret == false)
  {
    cliPrintf("ddr info\n");
    cliPrintf("ddr test [addr size(MB)\n");
  }
}
#endif

#endif