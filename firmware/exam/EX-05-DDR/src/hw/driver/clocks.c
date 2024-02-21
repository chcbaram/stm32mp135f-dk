#include "clocks.h"



#ifdef _USE_HW_CLOCKS
#include "cli.h"
#include "pmic.h"


#if CLI_USE(HW_CLOCKS)
static void cliCmd(cli_args_t *args);
#endif

static void clocksInitSetup(void);

static bool is_init = false;





bool clocksInit(void)
{
  bool ret = true;


  clocksInitSetup();

  is_init = ret;

#if CLI_USE(HW_CLOCKS)
  cliAdd("clocks", cliCmd);
#endif
  return ret;
}

void clocksInitSetup(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStructure;
  RCC_OscInitTypeDef RCC_OscInitStructure;

  /*
   * 1ms delay for voltage stabilization
   * The PMIC BUCK1 has 2.3 mV/μs min slew rate.
   * so the rise time from 1.25V to 1.35V is around 44uS
   */
  HAL_Delay(1);

  /* Select HSI as clock parent for MPU before reconfiguring PLL1*/
  RCC_ClkInitStructure.ClockType         = RCC_CLOCKTYPE_MPU;
  RCC_ClkInitStructure.MPUInit.MPU_Clock = RCC_MPUSOURCE_HSI;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStructure) != HAL_OK)
  {
    /* HAL RCC configuration error */
    Error_Handler();
  }

  /* Do not change Oscillators configuration*/
  RCC_OscInitStructure.OscillatorType = RCC_OSCILLATORTYPE_NONE;

  /* Do not change configuration of PPL2, PLL3 and PLL4*/
  RCC_OscInitStructure.PLL2.PLLState = RCC_PLL_NONE;
  RCC_OscInitStructure.PLL3.PLLState = RCC_PLL_NONE;
  RCC_OscInitStructure.PLL4.PLLState = RCC_PLL_NONE;

  /* Configure new Value for PLL1 = 900MHz */
  /* Freq = ((HSE) / PLLM) * (PLLN / PLLP) */
  RCC_OscInitStructure.PLL.PLLState  = RCC_PLL_ON;
  RCC_OscInitStructure.PLL.PLLSource = RCC_PLL12SOURCE_HSE;
  RCC_OscInitStructure.PLL.PLLM      = 2;
  RCC_OscInitStructure.PLL.PLLN      = 75;
  RCC_OscInitStructure.PLL.PLLP      = 1;
  RCC_OscInitStructure.PLL.PLLQ      = 2;
  RCC_OscInitStructure.PLL.PLLR      = 2;
  RCC_OscInitStructure.PLL.PLLFRACV  = 0x0;
  RCC_OscInitStructure.PLL.PLLMODE   = RCC_PLL_FRACTIONAL;

  if (HAL_RCC_OscConfig(&RCC_OscInitStructure) != HAL_OK)
  {
    /* HAL RCC configuration error */
    Error_Handler();
  }

  /*** Clear MPU_RAM_LOWSPEED prior to increasing the MPU frequency ***/
  CLEAR_BIT(PWR->CR1, PWR_CR1_MPU_RAM_LOWSPEED);

  /* Select PLL1 as clock parent for MPU */
  RCC_ClkInitStructure.ClockType         = RCC_CLOCKTYPE_MPU;
  RCC_ClkInitStructure.MPUInit.MPU_Clock = RCC_MPUSOURCE_PLL1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStructure) != HAL_OK)
  {
    /* HAL RCC configuration error */
    Error_Handler();
  }
}


#if CLI_USE(HW_CLOCKS)
void cliCmd(cli_args_t *args)
{
  bool ret = false;


  if (args->argc == 1 && args->isStr(0, "info"))
  {
    cliPrintf("is_init     : %s\n", is_init ? "True":"False");
    ret = true;
  }

  if (ret == false)
  {
    cliPrintf("clocks info\n");
  }
}
#endif

#endif