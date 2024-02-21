#include "ddr.h"



#ifdef _USE_HW_DDR
#include "cli.h"



#if CLI_USE(HW_DDR)
static void cliCmd(cli_args_t *args);
#endif

static bool ddrInitSetup(void);

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
    logPrintf("ddr addr    : 0x%X\n", HW_DDR_ADDR);
    logPrintf("ddr size    : %d MB\n", HW_DDR_SIZE/1024/1024);    
    ret = true;
  }

  if (ret == false)
  {
    cliPrintf("ddr info\n");
  }
}
#endif

#endif