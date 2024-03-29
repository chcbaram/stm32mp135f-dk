/**
  ******************************************************************************
  * @file    stm32mp13xx_hal_iwdg.c
  * @author  MCD Application Team
  * @brief   IWDG HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Independent Watchdog (IWDG) peripheral:
  *           + Initialization and Start functions
  *           + IO operation functions
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  ==============================================================================
                    ##### IWDG Generic features #####
  ==============================================================================
  [..]
    (+) The IWDG can be started by either software or hardware (configurable
        through option byte).

    (+) The IWDG is clocked by Low-Speed clock (LSI) and thus stays active even
        if the main clock fails.

    (+) Once the IWDG is started, the LSI is forced ON and both can not be
        disabled. The counter starts counting down from the reset value (0xFFF).
        When it reaches the end of count value (0x000) a reset signal is
        generated (IWDG reset).

    (+) Whenever the key value 0x0000 AAAA is written in the IWDG_KR register,
        the IWDG_RLR value is reloaded in the counter and the watchdog reset is
        prevented.

    (+) The IWDG is implemented in the VDD voltage domain that is still functional
        in STOP and STANDBY mode (IWDG reset can wake-up from STANDBY).
        IWDGRST flag in RCC_CSR register can be used to inform when an IWDG
        reset occurs.

    (+) Debug mode : When the microcontroller enters debug mode (core halted),
        the IWDG counter either continues to work normally or stops, depending
        on DBG_IWDG_STOP configuration bit in DBG module, accessible through
        __HAL_DBGMCU_FREEZE_IWDG() and __HAL_DBGMCU_UNFREEZE_IWDG() macros

    [..] Min-max timeout value @32KHz (LSI): ~125us / ~32.7s
         The IWDG timeout may vary due to LSI frequency dispersion. STM32MP13xx
         devices provide the capability to measure the LSI frequency (LSI clock
         connected internally to TIM16 CH1 input capture). The measured value
         can be used to have an IWDG timeout with an acceptable accuracy.

                     ##### How to use this driver #####
  ==============================================================================
  [..]
    (#) Use IWDG using HAL_IWDG_Init() function to :
      (+) Enable instance by writing Start keyword in IWDG_KEY register. LSI
           clock is forced ON and IWDG counter starts downcounting.
      (+) Enable write access to configuration register: IWDG_PR, IWDG_RLR &
           IWDG_WINR.
      (+) Configure the IWDG prescaler and counter reload value. This reload
           value will be loaded in the IWDG counter each time the watchdog is
           reloaded, then the IWDG will start counting down from this value.
      (+) wait for status flags to be reset"
      (+) Depending on window parameter:
        (++) If Window Init parameter is same as Window register value,
             nothing more is done but reload counter value in order to exit
             function withy exact time base.
        (++) Else modify Window register. This will automatically reload
             watchdog counter.

    (#) Then the application program must refresh the IWDG counter at regular
        intervals during normal operation to prevent an MCU reset, using
        HAL_IWDG_Refresh() function.

     *** IWDG HAL driver macros list ***
     ====================================
     [..]
       Below the list of most used macros in IWDG HAL driver:
      (+) __HAL_IWDG_START: Enable the IWDG peripheral
      (+) __HAL_IWDG_RELOAD_COUNTER: Reloads IWDG counter with value defined in
          the reload register

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32mp13xx_hal.h"

/** @addtogroup STM32MP13xx_HAL_Driver
  * @{
  */

#ifdef HAL_IWDG_MODULE_ENABLED
/** @addtogroup IWDG
  * @brief IWDG HAL module driver.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup IWDG_Private_Defines IWDG Private Defines
  * @{
  */
/* Status register needs up to 5 LSI clock periods divided by the clock
   prescaler to be updated. The number of LSI clock periods is upper-rounded to
   6 for the timeout value calculation.
   The timeout value is also calculated using the highest prescaler (256) and
   the LSI_VALUE constant. The value of this constant can be changed by the user
   to take into account possible LSI clock period variations.
   The timeout value is multiplied by 1000 to be converted in milliseconds. */
#define HAL_IWDG_DEFAULT_TIMEOUT        ((6UL * 256UL * 1000UL) / LSI_VALUE)
#define IWDG_KERNEL_UPDATE_FLAGS        (IWDG_SR_EWU | IWDG_SR_WVU | IWDG_SR_RVU | IWDG_SR_PVU)
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup IWDG_Exported_Functions
  * @{
  */

/** @addtogroup IWDG_Exported_Functions_Group1
  *  @brief    Initialization and Start functions.
  *
@verbatim
 ===============================================================================
          ##### Initialization and Start functions #####
 ===============================================================================
 [..]  This section provides functions allowing to:
      (+) Initialize the IWDG according to the specified parameters in the
          IWDG_InitTypeDef of associated handle.
      (+) Manage Window option.
      (+) Once initialization is performed in HAL_IWDG_Init function, Watchdog
          is reloaded in order to exit function with correct time base.

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the IWDG according to the specified parameters in the
  *         IWDG_InitTypeDef and start watchdog. Before exiting function,
  *         watchdog is refreshed in order to have correct time base.
  * @param  hiwdg  pointer to a IWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IWDG_Init(IWDG_HandleTypeDef *hiwdg)
{
  uint32_t tickstart;

  /* Check the IWDG handle allocation */
  if (hiwdg == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_IWDG_ALL_INSTANCE(hiwdg->Instance));
  assert_param(IS_IWDG_PRESCALER(hiwdg->Init.Prescaler));
  assert_param(IS_IWDG_RELOAD(hiwdg->Init.Reload));
  assert_param(IS_IWDG_WINDOW(hiwdg->Init.Window));
  assert_param(IS_IWDG_EWI(hiwdg->Init.EWI));

#if (USE_HAL_IWDG_REGISTER_CALLBACKS == 1)
  /* Reset Callback pointers */
  if (hiwdg->EwiCallback == NULL)
  {
    hiwdg->EwiCallback = HAL_IWDG_EarlyWakeupCallback;
  }
  if (hiwdg->MspInitCallback == NULL)
  {
    hiwdg->MspInitCallback = HAL_IWDG_MspInit;
  }

  /* Init the low level hardware */
  hiwdg->MspInitCallback(hiwdg);
#else
  /* Init the low level hardware */
  HAL_IWDG_MspInit(hiwdg);
#endif /* USE_HAL_IWDG_REGISTER_CALLBACKS */

  /* Enable IWDG. LSI is turned on automatically */
  __HAL_IWDG_START(hiwdg);

  /* Enable write access to IWDG_PR, IWDG_RLR and IWDG_WINR registers by writing
  0x5555 in KR */
  IWDG_ENABLE_WRITE_ACCESS(hiwdg);

  /* Write to IWDG registers the Prescaler & Reload values to work with */
  hiwdg->Instance->PR = hiwdg->Init.Prescaler;
  hiwdg->Instance->RLR = hiwdg->Init.Reload;

  if (hiwdg->Init.EWI == IWDG_EWI_DISABLE)
  {
    /* EWI comparator value different from 0,
     * Disable the early wakeup interrupt
     * acknowledge the early wakeup interrupt in any cases. it clears the EWIF flag in SR register
     * Set Watchdog Early Wakeup Comparator to 0x00
     */
    hiwdg->Instance->EWCR = IWDG_EWCR_EWIC;
  }
  else
  {
    /* EWI comparator value different from 0,
     * Enable the early wakeup interrupt
     * acknowledge the early wakeup interrupt in any cases. it clears the EWIF flag in SR register
     * Set Watchdog Early Wakeup Comparator value
     */
    hiwdg->Instance->EWCR = IWDG_EWCR_EWIE | IWDG_EWCR_EWIC | hiwdg->Init.EWI;
  }
  /* Check pending flag, if previous update not done, return timeout */
  tickstart = HAL_GetTick();

#if defined IWDG_SR_ONF
  /* Wait for register to be updated */
  while (hiwdg->Instance->SR != 0x100u)
  {
    if ((HAL_GetTick() - tickstart) > HAL_IWDG_DEFAULT_TIMEOUT)
    {
      return HAL_TIMEOUT;
    }
  }
#else
  /* Wait for register to be updated */
  while (hiwdg->Instance->SR != 0x00u)
  {
    if ((HAL_GetTick() - tickstart) > HAL_IWDG_DEFAULT_TIMEOUT)
    {
      return HAL_TIMEOUT;
    }
  }
#endif /* IWDG_SR_ONF */

  /* If window parameter is different than current value, modify window
  register */
  if (hiwdg->Instance->WINR != hiwdg->Init.Window)
  {
    /* Write to IWDG WINR the IWDG_Window value to compare with. In any case,
    even if window feature is disabled, Watchdog will be reloaded by writing
    windows register */
    hiwdg->Instance->WINR = hiwdg->Init.Window;
  }
  else
  {
    /* Reload IWDG counter with value defined in the reload register */
    __HAL_IWDG_RELOAD_COUNTER(hiwdg);
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initialize the IWDG MSP.
  * @param  hiwdg  pointer to a IWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @note   When rewriting this function in user file, mechanism may be added
  *         to avoid multiple initialize when HAL_IWDG_Init function is called
  *         again to change parameters.
  * @retval None
  */
__weak void HAL_IWDG_MspInit(IWDG_HandleTypeDef *hiwdg)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hiwdg);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_IWDG_MspInit could be implemented in the user file
   */
}


#if (USE_HAL_IWDG_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User IWDG Callback
  *         To be used instead of the weak (surcharged) predefined callback
  * @param  hiwdg IWDG handle
  * @param  CallbackID ID of the callback to be registered
  *         This parameter can be one of the following values:
  *           @arg @ref HAL_IWDG_EWI_CB_ID Early WakeUp Interrupt Callback ID
  *           @arg @ref HAL_IWDG_MSPINIT_CB_ID MspInit callback ID
  * @param  pCallback pointer to the Callback function
  * @retval status
  */
HAL_StatusTypeDef HAL_IWDG_RegisterCallback(IWDG_HandleTypeDef *hiwdg, HAL_IWDG_CallbackIDTypeDef CallbackID,
                                            pIWDG_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    switch (CallbackID)
    {
      case HAL_IWDG_EWI_CB_ID:
        hiwdg->EwiCallback = pCallback;
        break;
      case HAL_IWDG_MSPINIT_CB_ID:
        hiwdg->MspInitCallback = pCallback;
        break;

      default:
        status = HAL_ERROR;
        break;
    }
  }

  return status;
}


/**
  * @brief  Unregister a IWDG Callback
  *         IWDG Callback is redirected to the weak (surcharged) predefined callback
  * @param  hiwdg IWDG handle
  * @param  CallbackID ID of the callback to be registered
  *         This parameter can be one of the following values:
  *           @arg @ref HAL_IWDG_EWI_CB_ID Early WakeUp Interrupt Callback ID
  *           @arg @ref HAL_IWDG_MSPINIT_CB_ID MspInit callback ID
  * @retval status
  */
HAL_StatusTypeDef HAL_IWDG_UnRegisterCallback(IWDG_HandleTypeDef *hiwdg, HAL_IWDG_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  switch (CallbackID)
  {
    case HAL_IWDG_EWI_CB_ID:
      hiwdg->EwiCallback = HAL_IWDG_EarlyWakeupCallback;
      break;
    case HAL_IWDG_MSPINIT_CB_ID:
      hiwdg->MspInitCallback = HAL_IWDG_MspInit;
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}
#endif /*USE_HAL_IWDG_REGISTER_CALLBACKS*/
/**
  * @}
  */


/** @addtogroup IWDG_Exported_Functions_Group2
  *  @brief   IO operation functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
 [..]  This section provides functions allowing to:
      (+) Refresh the IWDG.

@endverbatim
  * @{
  */


/**
  * @brief  Refresh the IWDG.
  * @param  hiwdg  pointer to a IWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IWDG_Refresh(IWDG_HandleTypeDef *hiwdg)
{
  /* Reload IWDG counter with value defined in the reload register */
  __HAL_IWDG_RELOAD_COUNTER(hiwdg);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Handle IWDG interrupt request.
  * @note   The Early Wakeup Interrupt (EWI) can be used if specific safety operations
  *         or data logging must be performed before the actual reset is generated.
  *         The EWI interrupt is enabled by calling HAL_IWDG_Init function with
  *         EWIMode set to IWDG_EWI_ENABLE.
  *         When the downcounter reaches the value 0x40, and EWI interrupt is
  *         generated and the corresponding Interrupt Service Routine (ISR) can
  *         be used to trigger specific actions (such as communications or data
  *         logging), before resetting the device.
  * @param  hiwdg  pointer to a IWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @retval None
  */
void HAL_IWDG_IRQHandler(IWDG_HandleTypeDef *hiwdg)
{
  /* Check if IWDG Early Wakeup Interrupt occurred */
  if ((hiwdg->Instance->SR & IWDG_SR_EWIF) != 0x00u)
  {
    /* Clear the IWDG Early Wakeup flag */
    hiwdg->Instance->EWCR |= IWDG_EWCR_EWIC;

#if (USE_HAL_IWDG_REGISTER_CALLBACKS == 1)
    /* Early Wakeup registered callback */
    hiwdg->EwiCallback(hiwdg);
#else
    /* Early Wakeup callback */
    HAL_IWDG_EarlyWakeupCallback(hiwdg);
#endif /* USE_HAL_IWDG_REGISTER_CALLBACKS */
  }
}


/**
  * @brief  IWDG Early Wakeup callback.
  * @param  hiwdg  pointer to a IWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @retval None
  */
__weak void HAL_IWDG_EarlyWakeupCallback(IWDG_HandleTypeDef *hiwdg)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hiwdg);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_IWDG_EarlyWakeupCallback could be implemented in the user file
   */
}
/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_IWDG_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */
