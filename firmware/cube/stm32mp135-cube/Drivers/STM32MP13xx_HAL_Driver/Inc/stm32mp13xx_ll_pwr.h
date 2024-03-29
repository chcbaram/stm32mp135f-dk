/**
  ******************************************************************************
  * @file    stm32mp13xx_ll_pwr.h
  * @author  MCD Application Team
  * @brief   Header file of PWR LL module.
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
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP13xx_LL_PWR_H
#define STM32MP13xx_LL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp13xx.h"

/** @addtogroup STM32MP13xx_LL_Driver
  * @{
  */

#if defined(PWR)

/** @defgroup PWR_LL PWR
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup PWR_LL_Private_Constants PWR Private Constants
  * @{
  */

/** @defgroup PWR_LL_WAKEUP_PIN_OFFSET Wake-Up Pins register offsets Defines
  * @brief    Flags defines which can be used with LL_PWR_WriteReg function
  * @{
  */
/* Wake-Up Pins PWR register offsets */
#define LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET    2UL
#define LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK       0x1FU
/**
  * @}
  */
/**
  * @}
  */
/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_LL_EC_CLEAR_FLAG Clear Flags Defines
  * @brief    Flags defines which can be used with LL_PWR_WriteReg function
  * @{
  */
#define LL_PWR_FLAG_CPU_CSSF          PWR_MPUCR_CSSF      /*!< Clear MPU STANDBY, STOP flags */
#define LL_PWR_FLAG_WKUPCR_WKUPC1     PWR_WKUPCR_WKUPC1   /*!< Clear WKUP pin 1 */
#define LL_PWR_FLAG_WKUPCR_WKUPC2     PWR_WKUPCR_WKUPC2   /*!< Clear WKUP pin 2 */
#define LL_PWR_FLAG_WKUPCR_WKUPC3     PWR_WKUPCR_WKUPC3   /*!< Clear WKUP pin 3 */
#define LL_PWR_FLAG_WKUPCR_WKUPC4     PWR_WKUPCR_WKUPC4   /*!< Clear WKUP pin 4 */
#define LL_PWR_FLAG_WKUPCR_WKUPC5     PWR_WKUPCR_WKUPC5   /*!< Clear WKUP pin 5 */
#define LL_PWR_FLAG_WKUPCR_WKUPC6     PWR_WKUPCR_WKUPC6   /*!< Clear WKUP pin 6 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_PWR_ReadReg function
  * @{
  */
#define LL_PWR_FLAG_AVDO              PWR_CSR1_AVDO           /*!< Analog Voltage Detect Output */
#define LL_PWR_FLAG_PVDO              PWR_CSR1_PVDO           /*!< Power voltage detector output flag */

#define LL_PWR_FLAG_VBATL             PWR_CR2_VBATL           /*!< VBAT low threshold flag */
#define LL_PWR_FLAG_VBATH             PWR_CR2_VBATH           /*!< VBAT high threshold flag */
#define LL_PWR_FLAG_TEMPL             PWR_CR2_TEMPL           /*!< Temperature low threshold flag */
#define LL_PWR_FLAG_TEMPH             PWR_CR2_TEMPH           /*!< Temperature high threshold flag */

#define LL_PWR_FLAG_BRRDY             PWR_CR2_BRRDY           /*!< Backup Regulator ready flag */

#define LL_PWR_FLAG_VDDSD1RDY         PWR_CR3_VDDSD1RDY       /*!< VDDSD1 supply ready */
#define LL_PWR_FLAG_VDDSD2RDY         PWR_CR3_VDDSD2RDY       /*!< VDDSD2 supply ready */
#define LL_PWR_FLAG_USBRDY            PWR_CR3_USB33RDY        /*!< USB supply ready flag */
#define LL_PWR_FLAG_R18RDY            PWR_CR3_REG18RDY        /*!< 1V8 regulator supply ready */
#define LL_PWR_FLAG_R11RDY            PWR_CR3_REG11RDY        /*!< 1V1 regulator supply ready */


#define LL_PWR_WKUPFR_WKUPF1          PWR_WKUPFR_WKUPF1       /*!< Wakeup Pin Flag 1 */
#define LL_PWR_WKUPFR_WKUPF2          PWR_WKUPFR_WKUPF2       /*!< Wakeup Pin Flag 2 */
#define LL_PWR_WKUPFR_WKUPF3          PWR_WKUPFR_WKUPF3       /*!< Wakeup Pin Flag 3 */
#define LL_PWR_WKUPFR_WKUPF4          PWR_WKUPFR_WKUPF4       /*!< Wakeup Pin Flag 4 */
#define LL_PWR_WKUPFR_WKUPF5          PWR_WKUPFR_WKUPF5       /*!< Wakeup Pin Flag 5 */
#define LL_PWR_WKUPFR_WKUPF6          PWR_WKUPFR_WKUPF6       /*!< Wakeup Pin Flag 6 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_MODE_PWR_DOWN_DSMODE Power Down Deep Sleep mode
  * @{
  */
#define LL_PWR_MPU_MODE_STOP        0x00000000U           /*!< Keep System STOP mode when MCU enters to CSTOP or keep System LPLV-Stop2 mode when MPU enters to CSTANBY */
#define LL_PWR_MPU_MODE_STANDBY     PWR_MPUCR_PDDS        /*!< Allow System STANDBY mode when MPU enters to CSTANBY */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_REGU_MODE_DS_MODE  External Regulator Stop Mode In Deep Sleep Mode
  * @{
  */
#define LL_PWR_REGU_DSMODE_MAIN           0x00000000U   /*!< External Voltage Regulator in main mode during deepsleep mode */
#define LL_PWR_REGU_DSMODE_LOW_POWER      PWR_CR1_LPDS  /*!< External Voltage Regulator in low-power stop mode during deepsleep mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_POWER_MODE_PIN_CONFIG  Power Mode Pin Configuration
  * @{
  */
#define LL_PWR_PIN_CONFIG_STANDBY         0x00000000U    /*!< Power mode pin configuration for standby mode */
#define LL_PWR_PIN_CONFIG_LOW_POWER       PWR_CR1_LPCFG  /*!< Power mode pin configuration for all low power modes */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_POWER_LOW_VOLTAGE_DS_MODE  Low Voltage Deep Sleep LPLV Stop mode
  * @{
  */
#define LL_PWR_LVDS_LPSTOP_MODE           0x00000000U   /*!< LP-Stop mode */
#define LL_PWR_LVDS_LPLVSTOP_MODE         PWR_CR1_LVDS  /*!< LPLV-Stop mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_POWER_STOP2_MODE  System Low Voltage Low Voltage Stop2 mode
  * @{
  */
#define LL_PWR_SYSTEM_STOP_MODE           0x00000000U    /*!< System Stop mode */
#define LL_PWR_SYSTEM_LPLVSTOP2_MODE      PWR_CR1_STOP2  /*!< System LPLV-Stop2 mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_PVDLEVEL Programmable Voltage Detector Level
  * @{
  */
#define LL_PWR_PVDLEVEL_0   PWR_CR1_PLS_LEV0  /*!< Voltage threshold detected by PVD 1.95 V */
#define LL_PWR_PVDLEVEL_1   PWR_CR1_PLS_LEV1  /*!< Voltage threshold detected by PVD 2.1 V  */
#define LL_PWR_PVDLEVEL_2   PWR_CR1_PLS_LEV2  /*!< Voltage threshold detected by PVD 2.25 V */
#define LL_PWR_PVDLEVEL_3   PWR_CR1_PLS_LEV3  /*!< Voltage threshold detected by PVD 2.4 V  */
#define LL_PWR_PVDLEVEL_4   PWR_CR1_PLS_LEV4  /*!< Voltage threshold detected by PVD 2.55 V */
#define LL_PWR_PVDLEVEL_5   PWR_CR1_PLS_LEV5  /*!< Voltage threshold detected by PVD 2.7 V  */
#define LL_PWR_PVDLEVEL_6   PWR_CR1_PLS_LEV6  /*!< Voltage threshold detected by PVD 2.85 V */
#define LL_PWR_PVDLEVEL_7   PWR_CR1_PLS_LEV7  /*!< External voltage level on PVD_IN pin, compared to internal VREFINT level. */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_AVDLEVEL Analog Voltage Detector Level
  * @{
  */
#define LL_PWR_AVDLEVEL_0   PWR_CR1_ALS_LEV0  /*!< Analog Voltage threshold detected by AVD 1.7 V */
#define LL_PWR_AVDLEVEL_1   PWR_CR1_ALS_LEV1  /*!< Analog Voltage threshold detected by AVD 2.1 V */
#define LL_PWR_AVDLEVEL_2   PWR_CR1_ALS_LEV2  /*!< Analog Voltage threshold detected by AVD 2.5 V */
#define LL_PWR_AVDLEVEL_3   PWR_CR1_ALS_LEV3  /*!< Analog Voltage threshold detected by AVD 2.8 V */

/**
  * @}
  */

/** @defgroup PWR_LL_EC_BATT_CHARG_RESISTOR VBAT charging resistor selection
  * @{
  */
#define LL_PWR_BATT_CHARG_RESISTOR_5K     0x00000000U   /*!< Charge VBAT through a 5 kO resistor  */
#define LL_PWR_BATT_CHARGRESISTOR_1_5K    PWR_CR3_VBRS  /*!< Charge VBAT through a 1.5 kO resistor  */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN  MPU Wakeup Pins
  * @{
  */
#define LL_PWR_WAKEUP_PIN1    PWR_MPUWKUPENR_WKUPEN1  /*!< Wake-Up pin 1 : PA0  */
#define LL_PWR_WAKEUP_PIN2    PWR_MPUWKUPENR_WKUPEN2  /*!< Wake-Up pin 2 : PA2  */
#define LL_PWR_WAKEUP_PIN3    PWR_MPUWKUPENR_WKUPEN3  /*!< Wake-Up pin 3 : PC1  */
#define LL_PWR_WAKEUP_PIN4    PWR_MPUWKUPENR_WKUPEN4  /*!< Wake-Up pin 4 : PC13 */
#define LL_PWR_WAKEUP_PIN5    PWR_MPUWKUPENR_WKUPEN5  /*!< Wake-Up pin 5 : PI8  */
#define LL_PWR_WAKEUP_PIN6    PWR_MPUWKUPENR_WKUPEN6  /*!< Wake-Up pin 6 : PI11 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN_PULL  Wakeup Pins pull configuration
  * @{
  */
#define LL_PWR_WAKEUP_PIN_NOPULL      0x00000000UL   /*!< Configure Wake-Up pin in no pull */
#define LL_PWR_WAKEUP_PIN_PULLUP      0x00000001UL   /*!< Configure Wake-Up pin in pull Up */
#define LL_PWR_WAKEUP_PIN_PULLDOWN    0x00000002UL   /*!< Configure Wake-Up pin in pull Down */
/**
  * @}
  */

/**
  * @}
  */
/* Exported macro ------------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Macros PWR Exported Macros
  * @{
  */

/** @defgroup PWR_LL_EM_WRITE_READ Common write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in PWR register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_PWR_WriteReg(__REG__, __VALUE__) WRITE_REG(PWR->__REG__, (__VALUE__))

/**
  * @brief  Read a value in PWR register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_PWR_ReadReg(__REG__) READ_REG(PWR->__REG__)
/**
  * @}
  */

/**
  * @}
  */
/* Exported functions --------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_LL_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Set the voltage Regulator mode during deep sleep mode
  * @rmtoll CR1    LPDS         LL_PWR_SetRegulModeDS
  * @param  RegulMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_REGU_DSMODE_MAIN
  *         @arg @ref LL_PWR_REGU_DSMODE_LOW_POWER
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetRegulModeDS(uint32_t RegulMode)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_LPDS, RegulMode);
}

/**
  * @brief  Get the voltage Regulator mode during deep sleep mode
  * @rmtoll CR1    LPDS         LL_PWR_GetRegulModeDS
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_DSMODE_MAIN
  *         @arg @ref LL_PWR_REGU_DSMODE_LOW_POWER
  */
__STATIC_INLINE uint32_t LL_PWR_GetRegulModeDS(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_LPDS));
}

/**
  * @brief  Set the low power pin configuration
  * @rmtoll CR1    LPCFG         LL_PWR_SetPwrPinConfig
  * @param  PwrPinMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PIN_CONFIG_STANDBY
  *         @arg @ref LL_PWR_PIN_CONFIG_LOW_POWER
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPwrPinConfig(uint32_t PwrPinMode)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_LPCFG, PwrPinMode);
}

/**
  * @brief  Get the low power pin configuration
  * @rmtoll CR1    LPCFG        LL_PWR_GetPwrPinConfig
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_PIN_CONFIG_STANDBY
  *         @arg @ref LL_PWR_PIN_CONFIG_LOW_POWER
  */
__STATIC_INLINE uint32_t LL_PWR_GetPwrPinConfig(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_LPCFG));
}

/**
  * @brief  Set the low voltage deep sleep LPLV stop mode
  * @rmtoll CR1    LVDS         LL_PWR_SetLVDSStopMode
  * @param  StopMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_LVDS_LPSTOP_MODE
  *         @arg @ref LL_PWR_LVDS_LPLVSTOP_MODE
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetLVDSStopMode(uint32_t StopMode)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_LVDS, StopMode);
}

/**
  * @brief  Get the low voltage deep sleep LPLV stop mode
  * @rmtoll CR1    LVDS         LL_PWR_GetLVDSStopMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_LVDS_LPSTOP_MODE
  *         @arg @ref LL_PWR_LVDS_LPLVSTOP_MODE
  */
__STATIC_INLINE uint32_t LL_PWR_GetLVDSStopMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_LVDS));
}

/**
  * @brief  Set the system LPLV stop2 mode
  * @rmtoll CR1    STOP2         LL_PWR_SetLPLVStop2Mode
  * @param  Stop2Mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SYSTEM_STOP_MODE
  *         @arg @ref LL_PWR_SYSTEM_LPLVSTOP2_MODE
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetLPLVStop2Mode(uint32_t Stop2Mode)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_STOP2, Stop2Mode);
}

/**
  * @brief  Get the system LPLV stop2 mode
  * @rmtoll CR1    STOP2         LL_PWR_GetLPLVStop2Mode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SYSTEM_STOP_MODE
  *         @arg @ref LL_PWR_SYSTEM_LPLVSTOP2_MODE
  */
__STATIC_INLINE uint32_t LL_PWR_GetLPLVStop2Mode(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_STOP2));
}

/**
  * @brief  Enable Programmable Voltage Detector
  * @rmtoll CR1    PVDEN       LL_PWR_EnablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePVD(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_PVDEN);
}

/**
  * @brief  Disable Programmable Voltage Detector
  * @rmtoll CR1    PVDEN       LL_PWR_DisablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePVD(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_PVDEN);
}

/**
  * @brief  Check if Programmable Voltage Detector is enabled
  * @rmtoll CR1    PVDEN       LL_PWR_IsEnabledPVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVD(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_PVDEN) == (PWR_CR1_PVDEN)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the voltage threshold detected by the Programmable Voltage Detector
  * @rmtoll CR1    PLS       LL_PWR_SetPVDLevel
  * @param  PVDLevel This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_0
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPVDLevel(uint32_t PVDLevel)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_PLS, PVDLevel);
}

/**
  * @brief  Get the voltage threshold detection
  * @rmtoll CR1    PLS       LL_PWR_GetPVDLevel
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_0
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  */
__STATIC_INLINE uint32_t LL_PWR_GetPVDLevel(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_PLS));
}

/**
  * @brief  Enable access to the backup domain
  * @rmtoll CR1    DBP       LL_PWR_EnableBkUpAccess
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBkUpAccess(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_DBP);
}

/**
  * @brief  Disable access to the backup domain
  * @rmtoll CR1    DBP       LL_PWR_DisableBkUpAccess
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBkUpAccess(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_DBP);
}

/**
  * @brief  Check if the backup domain is enabled
  * @rmtoll CR1    DBP       LL_PWR_IsEnabledBkUpAccess
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBkUpAccess(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_DBP) == (PWR_CR1_DBP)) ? 1UL : 0UL);
}

/**
  * @brief  Enable MPU memories low speed
  * @rmtoll CR1    MPU_RAM_LOWSPEED       LL_PWR_EnableMpuRamLowSpeed
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableMpuRamLowSpeed(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_MPU_RAM_LOWSPEED);
}

/**
  * @brief  Disable MPU memories low speed
  * @rmtoll CR1    MPU_RAM_LOWSPEED       LL_PWR_DisableMpuRamLowSpeed
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableMpuRamLowSpeed(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_MPU_RAM_LOWSPEED);
}

/**
  * @brief  Check if MPU memories low speed is enabled
  * @rmtoll CR1    MPU_RAM_LOWSPEED       LL_PWR_IsEnabledMpuRamLowSpeed
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledMpuRamLowSpeed(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_MPU_RAM_LOWSPEED) == (PWR_CR1_MPU_RAM_LOWSPEED)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Analog Power Voltage Detector
  * @rmtoll CR1    AVDEN       LL_PWR_EnableAVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableAVD(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_AVDEN);
}

/**
  * @brief  Disable Analog Power Voltage Detector
  * @rmtoll CR1    AVDEN       LL_PWR_DisableAVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableAVD(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_AVDEN);
}

/**
  * @brief  Check if Analog Power Voltage Detector is enabled
  * @rmtoll CR1    AVDEN       LL_PWR_IsEnabledAVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledAVD(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_AVDEN) == (PWR_CR1_AVDEN)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the voltage threshold to be detected by the Analog Power Voltage Detector
  * @rmtoll CR1    ALS       LL_PWR_SetAVDLevel
  * @param  AVDLevel This parameter can be one of the following values:
  *         @arg @ref LL_PWR_AVDLEVEL_0
  *         @arg @ref LL_PWR_AVDLEVEL_1
  *         @arg @ref LL_PWR_AVDLEVEL_2
  *         @arg @ref LL_PWR_AVDLEVEL_3
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetAVDLevel(uint32_t AVDLevel)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_ALS, AVDLevel);
}

/**
  * @brief  Get the Analog Voltage threshold to be detected by the Analog Power Voltage Detector
  * @rmtoll CR1    ALS       LL_PWR_GetAVDLevel
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_AVDLEVEL_0
  *         @arg @ref LL_PWR_AVDLEVEL_1
  *         @arg @ref LL_PWR_AVDLEVEL_2
  *         @arg @ref LL_PWR_AVDLEVEL_3
  */
__STATIC_INLINE uint32_t LL_PWR_GetAVDLevel(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_ALS));
}

/**
  * @brief  Enable Backup Regulator
  * @rmtoll CR2    BREN       LL_PWR_EnableBkUpRegulator
  * @note When set, the Backup Regulator (used to maintain backup SRAM content
  *       in Standby and VBAT modes) is enabled. If BRE is reset, the backup
  *       Regulator is switched off. The backup SRAM can still be used in Run
  *       mode and Stop mode but its content will be lost in the Standby and VBAT
  *       modes. Once set, the application must wait that the Backup Regulator
  *       Ready flag (BRR) is set to indicate that the data written into the RAM
  *       will be maintained in the Standby and VBAT modes.
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBkUpRegulator(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_BREN);
}

/**
  * @brief  Disable Backup Regulator
  * @rmtoll CR2    BREN       LL_PWR_DisableBkUpRegulator
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBkUpRegulator(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_BREN);
}

/**
  * @brief  Check if the backup Regulator is enabled
  * @rmtoll CR2    BREN      LL_PWR_IsEnabledBkUpRegulator
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBkUpRegulator(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_BREN) == (PWR_CR2_BREN)) ? 1UL : 0UL);
}


/**
  * @brief  Enable VBAT and Temperature monitoring
  * @rmtoll CR2    MONEN       LL_PWR_EnableMonitoring
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableMonitoring(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_MONEN);
}

/**
  * @brief  Disable VBAT and Temperature monitoring
  * @rmtoll CR2    MONEN       LL_PWR_DisableMonitoring
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableMonitoring(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_MONEN);
}

/**
  * @brief  Check if the VBAT and Temperature monitoring is enabled
  * @rmtoll CR2    MONEN      LL_PWR_IsEnabledMonitoring
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledMonitoring(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_MONEN) == (PWR_CR2_MONEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable battery charging
  * @rmtoll CR3          VBE           LL_PWR_EnableBatteryCharging
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBatteryCharging(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_VBE);
}

/**
  * @brief  Disable battery charging
  * @rmtoll CR3          VBE           LL_PWR_DisableBatteryCharging
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBatteryCharging(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_VBE);
}

/**
  * @brief  Check if battery charging is enabled
  * @rmtoll CR3          VBE           LL_PWR_IsEnabledBatteryCharging
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBatteryCharging(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_VBE) == (PWR_CR3_VBE)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Battery charge resistor impedance
  * @rmtoll CR3          VBRS          LL_PWR_SetBattChargResistor
  * @param  Resistor This parameter can be one of the following values:
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_5K
  *         @arg @ref LL_PWR_BATT_CHARGRESISTOR_1_5K
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetBattChargResistor(uint32_t Resistor)
{
  MODIFY_REG(PWR->CR3, PWR_CR3_VBRS, Resistor);
}

/**
  * @brief  Get the Battery charge resistor impedance
  * @rmtoll CR3          VBRS          LL_PWR_GetBattChargResistor
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_5K
  *         @arg @ref LL_PWR_BATT_CHARGRESISTOR_1_5K
  */
__STATIC_INLINE uint32_t LL_PWR_GetBattChargResistor(void)
{
  return (uint32_t)(READ_BIT(PWR->CR3, PWR_CR3_VBRS));
}

/**
  * @brief  Enable the ddr self-refresh in standby mode
  * @rmtoll CR3          DDRSREN           LL_PWR_EnableDdrSelfRefresh
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableDdrSelfRefresh(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_DDRSREN);
}

/**
  * @brief  Disable the ddr self-refresh in standby mode
  * @rmtoll CR3          DDRSREN           LL_PWR_DisableDdrSelfRefresh
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableDdrSelfRefresh(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_DDRSREN);
}

/**
  * @brief  Check if the ddr self-refresh in standby mode is enabled
  * @rmtoll CR3          DDRSREN           LL_PWR_IsEnabledDdrSelfRefresh
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledDdrSelfRefresh(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_DDRSREN) == (PWR_CR3_DDRSREN)) ? 1UL : 0UL);
}

/**
  * @brief  Disable the ddr self-refresh retention after standby mode
  * @rmtoll CR3          DDRSRDIS           LL_PWR_DisableDdrSelfRefreshRetention
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableDdrSelfRefreshRetention(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_DDRSRDIS);
}

/**
  * @brief  Check if the ddr self-refresh retention after standby mode is enabled
  * @rmtoll CR3          DDRSRDIS           LL_PWR_IsEnabledDdrSelfRefreshRetention
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledDdrSelfRefreshRetention(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_DDRSRDIS) == (PWR_CR3_DDRSRDIS)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the ddr retention
  * @rmtoll CR3          DDRRETEN           LL_PWR_EnableDdrRetention
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableDdrRetention(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_DDRRETEN);
}

/**
  * @brief  Disable the ddr retention
  * @rmtoll CR3          DDRRETEN           LL_PWR_DisableDdrRetention
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableDdrRetention(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_DDRRETEN);
}

/**
  * @brief  Check if the ddr retention is enabled
  * @rmtoll CR3          DDRRETEN           LL_PWR_IsEnabledDdrRetention
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledDdrRetention(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_DDRRETEN) == (PWR_CR3_DDRRETEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the VDDSD1 voltage level detector
  * @rmtoll CR3          VDDSD1DEN           LL_PWR_EnableVDDSD1VoltageDetector
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableVDDSD1VoltageDetector(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_VDDSD1DEN);
}

/**
  * @brief  Disable the VDDSD1 voltage level detector
  * @rmtoll CR3          VDDSD1DEN           LL_PWR_DisableVDDSD1VoltageDetector
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableVDDSD1VoltageDetector(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_VDDSD1DEN);
}

/**
  * @brief  Check if the VDDSD1 voltage level detector is enabled
  * @rmtoll CR3          VDDSD1DEN           LL_PWR_IsEnabledVDDSD1VoltageDetector
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVDDSD1VoltageDetector(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_VDDSD1DEN) == (PWR_CR3_VDDSD1DEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the VDDSD2 voltage level detector
  * @rmtoll CR3          VDDSD2DEN           LL_PWR_EnableVDDSD2VoltageDetector
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableVDDSD2VoltageDetector(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_VDDSD2DEN);
}

/**
  * @brief  Disable the VDDSD2 voltage level detector
  * @rmtoll CR3          VDDSD2DEN           LL_PWR_DisableVDDSD2VoltageDetector
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableVDDSD2VoltageDetector(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_VDDSD2DEN);
}

/**
  * @brief  Check if the VDDSD2 voltage level detector is enabled
  * @rmtoll CR3          VDDSD2DEN           LL_PWR_IsEnabledVDDSD2VoltageDetector
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVDDSD2VoltageDetector(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_VDDSD2DEN) == (PWR_CR3_VDDSD2DEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the VDDSD1 override voltage level detector
  * @rmtoll CR3          VDDSD1VALID           LL_PWR_EnableVDDSD1OverrideVoltageDetector
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableVDDSD1OverrideVoltageDetector(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_VDDSD1VALID);
}

/**
  * @brief  Disable the VDDSD1 override voltage level detector
  * @rmtoll CR3          VDDSD1VALID           LL_PWR_DisableVDDSD1OverrideVoltageDetector
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableVDDSD1OverrideVoltageDetector(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_VDDSD1VALID);
}

/**
  * @brief  Check if the VDDSD1 override voltage level detector is enabled
  * @rmtoll CR3          VDDSD1VALID           LL_PWR_IsEnabledVDDSD1OverrideVoltageDetector
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVDDSD1OverrideVoltageDetector(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_VDDSD1VALID) == (PWR_CR3_VDDSD1VALID)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the VDDSD2 override voltage level detector
  * @rmtoll CR3          VDDSD2VALID           LL_PWR_EnableVDDSD2OverrideVoltageDetector
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableVDDSD2OverrideVoltageDetector(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_VDDSD2VALID);
}

/**
  * @brief  Disable the VDDSD2 override voltage level detector
  * @rmtoll CR3          VDDSD2VALID           LL_PWR_DisableVDDSD2OverrideVoltageDetector
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableVDDSD2OverrideVoltageDetector(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_VDDSD2VALID);
}

/**
  * @brief  Check if the VDDSD2 override voltage level detector is enabled
  * @rmtoll CR3          VDDSD2VALID           LL_PWR_IsEnabledVDDSD2OverrideVoltageDetector
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVDDSD2OverrideVoltageDetector(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_VDDSD2VALID) == (PWR_CR3_VDDSD2VALID)) ? 1UL : 0UL);
}


/**
  * @brief  Enable 1V1 regulator
  * @rmtoll CR3          REG11EN           LL_PWR_Enable1V1Regulator
  * @retval None
  */
__STATIC_INLINE void LL_PWR_Enable1V1Regulator(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_REG11EN);
}

/**
  * @brief  Disable the 1V1 regulator
  * @rmtoll CR3          REG11EN           LL_PWR_Disable1V1Regulator
  * @retval None
  */
__STATIC_INLINE void LL_PWR_Disable1V1Regulator(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_REG11EN);
}

/**
  * @brief  Check if the 1V1 regulator is enabled
  * @rmtoll CR3          REG11EN           LL_PWR_IsEnabled1V1Regulator
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabled1V1Regulator(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_REG11EN) == (PWR_CR3_REG11EN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable 1V8 regulator
  * @rmtoll CR3          REG18EN           LL_PWR_Enable1V8Regulator
  * @retval None
  */
__STATIC_INLINE void LL_PWR_Enable1V8Regulator(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_REG18EN);
}

/**
  * @brief  Disable the 1V8 regulator
  * @rmtoll CR3          REG18EN           LL_PWR_Disable1V8Regulator
  * @retval None
  */
__STATIC_INLINE void LL_PWR_Disable1V8Regulator(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_REG18EN);
}

/**
  * @brief  Check if the 1V8 regulator is enabled
  * @rmtoll CR3          REG18EN           LL_PWR_IsEnabled1V8Regulator
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabled1V8Regulator(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_REG18EN) == (PWR_CR3_REG18EN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the USB voltage detector
  * @rmtoll CR3          USB33DEN           LL_PWR_EnableUSBVoltageDetector
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableUSBVoltageDetector(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_USB33DEN);
}

/**
  * @brief  Disable the USB voltage detector
  * @rmtoll CR3          USB33DEN           LL_PWR_DisableUSBVoltageDetector
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableUSBVoltageDetector(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_USB33DEN);
}

/**
  * @brief  Check if the USB voltage detector is enabled
  * @rmtoll CR3          USB33DEN           LL_PWR_IsEnabledUSBVoltageDetector
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUSBVoltageDetector(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_USB33DEN) == (PWR_CR3_USB33DEN)) ? 1UL : 0UL);
}


/**
  * @brief  Set the power down mode when MPU enters enters deepsleep
  * @rmtoll MPUCR     PDDS       LL_PWR_MPU_SetPowerMode\n
  * @param  PDMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_MPU_MODE_STOP
  *         @arg @ref LL_PWR_MPU_MODE_STANDBY
  * @retval None
  */
__STATIC_INLINE void LL_PWR_MPU_SetPowerMode(uint32_t PDMode)
{
  MODIFY_REG(PWR->MPUCR, PWR_MPUCR_PDDS, PDMode);
}

/**
  * @brief  Get the power down mode when MPU enters enters deepsleep
  * @rmtoll MPUCR     PDDS       LL_PWR_MPU_GetPowerMode\n
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_MPU_MODE_STOP
  *         @arg @ref LL_PWR_MPU_MODE_STANDBY
  */
__STATIC_INLINE uint32_t LL_PWR_MCU_GetPowerMode(void)
{
  return (uint32_t)(READ_BIT(PWR->MPUCR, PWR_MPUCR_PDDS));
}

/**
  * @brief  Enable the WakeUp PINx functionality
  * @rmtoll MCUWKUPENR   WKUPEN1       LL_PWR_EnableWakeUpPin\n
  *         MCUWKUPENR   WKUPEN2       LL_PWR_EnableWakeUpPin\n
  *         MCUWKUPENR   WKUPEN3       LL_PWR_EnableWakeUpPin\n
  *         MCUWKUPENR   WKUPEN4       LL_PWR_EnableWakeUpPin\n
  *         MCUWKUPENR   WKUPEN5       LL_PWR_EnableWakeUpPin\n
  *         MCUWKUPENR   WKUPEN6       LL_PWR_EnableWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableWakeUpPin(uint32_t WakeUpPin)
{
  SET_BIT(PWR->MPUWKUPENR, WakeUpPin);
}

/**
  * @brief  Disable the WakeUp PINx functionality
  * @rmtoll MCUWKUPENR   WKUPEN1       LL_PWR_DisableWakeUpPin\n
  *         MCUWKUPENR   WKUPEN2       LL_PWR_DisableWakeUpPin\n
  *         MCUWKUPENR   WKUPEN3       LL_PWR_DisableWakeUpPin\n
  *         MCUWKUPENR   WKUPEN4       LL_PWR_DisableWakeUpPin\n
  *         MCUWKUPENR   WKUPEN5       LL_PWR_DisableWakeUpPin\n
  *         MCUWKUPENR   WKUPEN6       LL_PWR_DisableWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableWakeUpPin(uint32_t WakeUpPin)
{
  CLEAR_BIT(PWR->MPUWKUPENR, WakeUpPin);
}

/**
  * @brief  Check if the WakeUp PINx functionality is enabled
  * @rmtoll MCUWKUPENR   WKUPEN1       LL_PWR_IsEnabledWakeUpPin\n
  *         MCUWKUPENR   WKUPEN2       LL_PWR_IsEnabledWakeUpPin\n
  *         MCUWKUPENR   WKUPEN3       LL_PWR_IsEnabledWakeUpPin\n
  *         MCUWKUPENR   WKUPEN4       LL_PWR_IsEnabledWakeUpPin\n
  *         MCUWKUPENR   WKUPEN5       LL_PWR_IsEnabledWakeUpPin\n
  *         MCUWKUPENR   WKUPEN6       LL_PWR_IsEnabledWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledWakeUpPin(uint32_t WakeUpPin)
{
  return ((READ_BIT(PWR->MPUWKUPENR, WakeUpPin) == (WakeUpPin)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Wake-Up pin polarity low for the event detection
  * @rmtoll WKUPCR   WKUPP1       LL_PWR_SetWakeUpPinPolarityLow\n
  *         WKUPCR   WKUPP2       LL_PWR_SetWakeUpPinPolarityLow\n
  *         WKUPCR   WKUPP3       LL_PWR_SetWakeUpPinPolarityLow\n
  *         WKUPCR   WKUPP4       LL_PWR_SetWakeUpPinPolarityLow\n
  *         WKUPCR   WKUPP5       LL_PWR_SetWakeUpPinPolarityLow\n
  *         WKUPCR   WKUPP6       LL_PWR_SetWakeUpPinPolarityLow
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityLow(uint32_t WakeUpPin)
{
  SET_BIT(PWR->WKUPCR, (WakeUpPin << PWR_WKUPCR_WKUPP_Pos));
}

/**
  * @brief  Set the Wake-Up pin polarity high for the event detection
  * @rmtoll WKUPCR   WKUPP1       LL_PWR_SetWakeUpPinPolarityHigh\n
  *         WKUPCR   WKUPP2       LL_PWR_SetWakeUpPinPolarityHigh\n
  *         WKUPCR   WKUPP3       LL_PWR_SetWakeUpPinPolarityHigh\n
  *         WKUPCR   WKUPP4       LL_PWR_SetWakeUpPinPolarityHigh\n
  *         WKUPCR   WKUPP5       LL_PWR_SetWakeUpPinPolarityHigh\n
  *         WKUPCR   WKUPP6       LL_PWR_SetWakeUpPinPolarityHigh
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityHigh(uint32_t WakeUpPin)
{
  CLEAR_BIT(PWR->WKUPCR, (WakeUpPin << PWR_WKUPCR_WKUPP_Pos));
}

/**
  * @brief  Get the Wake-Up pin polarity for the event detection
  * @rmtoll WKUPCR   WKUPP1       LL_PWR_IsWakeUpPinPolarityLow\n
  *         WKUPCR   WKUPP2       LL_PWR_IsWakeUpPinPolarityLow\n
  *         WKUPCR   WKUPP3       LL_PWR_IsWakeUpPinPolarityLow\n
  *         WKUPCR   WKUPP4       LL_PWR_IsWakeUpPinPolarityLow\n
  *         WKUPCR   WKUPP5       LL_PWR_IsWakeUpPinPolarityLow\n
  *         WKUPCR   WKUPP6       LL_PWR_IsWakeUpPinPolarityLow
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsWakeUpPinPolarityLow(uint32_t WakeUpPin)
{
  return ((READ_BIT(PWR->WKUPCR, (WakeUpPin << PWR_WKUPCR_WKUPP_Pos)) == (WakeUpPin << PWR_WKUPCR_WKUPP_Pos)) ?
          1UL : 0UL);
}

/**
  * @brief  Set the Wake-Up pin Pull None
  * @rmtoll WKUPCR   WKUPPUPD1       LL_PWR_SetWakeUpPinPullNone\n
  *         WKUPCR   WKUPPUPD2       LL_PWR_SetWakeUpPinPullNone\n
  *         WKUPCR   WKUPPUPD3       LL_PWR_SetWakeUpPinPullNone\n
  *         WKUPCR   WKUPPUPD4       LL_PWR_SetWakeUpPinPullNone\n
  *         WKUPCR   WKUPPUPD5       LL_PWR_SetWakeUpPinPullNone\n
  *         WKUPCR   WKUPPUPD6       LL_PWR_SetWakeUpPinPullNone
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPullNone(uint32_t WakeUpPin)
{
  MODIFY_REG(PWR->WKUPCR, \
             (PWR_WKUPCR_WKUPPUPD1 << ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * POSITION_VAL(WakeUpPin)) &
                                       LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)),
             (LL_PWR_WAKEUP_PIN_NOPULL << ((PWR_WKUPCR_WKUPPUPD1_Pos +
                                            (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * POSITION_VAL(WakeUpPin))) &
                                           LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)));
}

/**
  * @brief  Set the Wake-Up pin Pull Up
  * @rmtoll WKUPCR   WKUPPUPD1       LL_PWR_SetWakeUpPinPullUp\n
  *         WKUPCR   WKUPPUPD2       LL_PWR_SetWakeUpPinPullUp\n
  *         WKUPCR   WKUPPUPD3       LL_PWR_SetWakeUpPinPullUp\n
  *         WKUPCR   WKUPPUPD4       LL_PWR_SetWakeUpPinPullUp\n
  *         WKUPCR   WKUPPUPD5       LL_PWR_SetWakeUpPinPullUp\n
  *         WKUPCR   WKUPPUPD6       LL_PWR_SetWakeUpPinPullUp
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPullUp(uint32_t WakeUpPin)
{
  MODIFY_REG(PWR->WKUPCR, (PWR_WKUPCR_WKUPPUPD1 << ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * POSITION_VAL(WakeUpPin)) & \
                                                    LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)), (LL_PWR_WAKEUP_PIN_PULLUP << \
                                                        ((PWR_WKUPCR_WKUPPUPD1_Pos + \
                                                          (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET  \
                                                           *POSITION_VAL(WakeUpPin))) & \
                                                         LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)));
}

/**
  * @brief  Set the Wake-Up pin Pull Down
  * @rmtoll WKUPCR   WKUPPUPD1       LL_PWR_SetWakeUpPinPullDown\n
  *         WKUPCR   WKUPPUPD2       LL_PWR_SetWakeUpPinPullDown\n
  *         WKUPCR   WKUPPUPD3       LL_PWR_SetWakeUpPinPullDown\n
  *         WKUPCR   WKUPPUPD4       LL_PWR_SetWakeUpPinPullDown\n
  *         WKUPCR   WKUPPUPD5       LL_PWR_SetWakeUpPinPullDown\n
  *         WKUPCR   WKUPPUPD6       LL_PWR_SetWakeUpPinPullDown
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPullDown(uint32_t WakeUpPin)
{
  MODIFY_REG(PWR->WKUPCR, (PWR_WKUPCR_WKUPPUPD1 << ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * POSITION_VAL(WakeUpPin)) & \
                                                    LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)), \
             (LL_PWR_WAKEUP_PIN_PULLDOWN << ((PWR_WKUPCR_WKUPPUPD1_Pos + \
                                              (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * POSITION_VAL(WakeUpPin))) & \
                                             LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)));
}

/**
  * @brief  Get the Wake-Up pin pull
  * @rmtoll WKUPCR   WKUPPUPD1       LL_PWR_GetWakeUpPinPull\n
  *         WKUPCR   WKUPPUPD2       LL_PWR_GetWakeUpPinPull\n
  *         WKUPCR   WKUPPUPD3       LL_PWR_GetWakeUpPinPull\n
  *         WKUPCR   WKUPPUPD4       LL_PWR_GetWakeUpPinPull\n
  *         WKUPCR   WKUPPUPD5       LL_PWR_GetWakeUpPinPull\n
  *         WKUPCR   WKUPPUPD6       LL_PWR_GetWakeUpPinPull
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_NOPULL
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULLUP
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULLDOWN
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeUpPinPull(uint32_t WakeUpPin)
{
  register uint32_t regValue = READ_BIT(PWR->WKUPCR,
                                        (PWR_WKUPCR_WKUPPUPD1 <<
                                         ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * POSITION_VAL(WakeUpPin)) &
                                          LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)));

  return (uint32_t)(regValue >> ((PWR_WKUPCR_WKUPPUPD1_Pos + (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * POSITION_VAL(
                                                                WakeUpPin))) & LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK));
}

/**
  * @}
  */

/** @defgroup PWR_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Indicate whether VDD voltage is below the selected PVD threshold
  * @rmtoll CSR1   PVDO       LL_PWR_IsActiveFlag_PVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_PVDO(void)
{
  return ((READ_BIT(PWR->CSR1, PWR_CSR1_PVDO) == (PWR_CSR1_PVDO)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether VDDA voltage is below the selected AVD threshold
  * @rmtoll CSR1   AVDO       LL_PWR_IsActiveFlag_AVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_AVDO(void)
{
  return ((READ_BIT(PWR->CSR1, PWR_CSR1_AVDO) == (PWR_CSR1_AVDO)) ? 1UL : 0UL);
}

/**
  * @brief  Get Backup Regulator ready Flag
  * @rmtoll CR2   BRRDY       LL_PWR_IsActiveFlag_BRR
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_BRR(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_BRRDY) == (PWR_CR2_BRRDY)) ? 1UL : 0UL);
}


/**
  * @brief  Indicate whether the VBAT level is equal or below low threshold
  * @rmtoll CR2   VBATL       LL_PWR_IsActiveFlag_VBATL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VBATL(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_VBATL) == (PWR_CR2_VBATL)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VBAT level is equal or above high threshold
  * @rmtoll CR2   VBATH       LL_PWR_IsActiveFlag_VBATH
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VBATH(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_VBATH) == (PWR_CR2_VBATH)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the device temperature level is equal or below low threshold
  * @rmtoll CR2   TEMPL       LL_PWR_IsActiveFlag_TEMPL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_TEMPL(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_TEMPL) == (PWR_CR2_TEMPL)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the CPU temperature level is equal or above high threshold
  * @rmtoll CR2   TEMPH       LL_PWR_IsActiveFlag_TEMPH
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_TEMPH(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_TEMPH) == (PWR_CR2_TEMPH)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the USB supply is ready or not
  * @rmtoll CR3   USBRDY       LL_PWR_IsActiveFlag_USB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_USB(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_USB33RDY) == (PWR_CR3_USB33RDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the 1V1 regulator is ready or not
  * @rmtoll CR3   REG11RDY       LL_PWR_IsActiveFlag_R1V1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_R1V1(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_REG11RDY) == (PWR_CR3_REG11RDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the 1V8 regulator is ready or not
  * @rmtoll CR3   REG18RDY       LL_PWR_IsActiveFlag_R1V8
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_R1V8(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_REG18RDY) == (PWR_CR3_REG18RDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VDD supply D1 is ready or not
  * @rmtoll CR3   USBRDY       LL_PWR_IsActiveFlag_VDDSD1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VDDSD1(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_VDDSD1RDY) == (PWR_CR3_VDDSD1RDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VDD supply D2 is ready or not
  * @rmtoll CR3   USBRDY       LL_PWR_IsActiveFlag_VDDSD2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VDDSD2(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_VDDSD2RDY) == (PWR_CR3_VDDSD2RDY)) ? 1UL : 0UL);
}



/**
  * @brief  Get Stop Flag
  * @rmtoll MPUCR   STOPF       LL_PWR_MPU_IsActiveFlag_STOP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_MPU_IsActiveFlag_STOP(void)
{
  return ((READ_BIT(PWR->MPUCR, PWR_MPUCR_STOPF) == (PWR_MPUCR_STOPF)) ? 1UL : 0UL);
}

/**
  * @brief  Get System Standby Flag
  * @rmtoll MPUCR   SBF       LL_PWR_MPU_IsActiveFlag_SB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_MPU_IsActiveFlag_SB(void)
{
  return ((READ_BIT(PWR->MPUCR, PWR_MPUCR_SBF) == (PWR_MPUCR_SBF)) ? 1UL : 0UL);
}

/**
  * @brief  Get MPU Standby Flag
  * @rmtoll MPUCR   SBFMPU       LL_PWR_MPU_IsActiveFlag_SBMPU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_MPU_IsActiveFlag_SBMPU(void)
{
  return ((READ_BIT(PWR->MPUCR, PWR_MPUCR_SBF_MPU) == (PWR_MPUCR_SBF_MPU)) ? 1UL : 0UL);
}

/**
  * @brief  Get MPU System idle Flag
  * @rmtoll MPUCR   STANDBYWFIL2       LL_PWR_MPU_IsActiveFlag_STANDBYWFIL2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_MPU_IsActiveFlag_STANDBYWFIL2(void)
{
  return ((READ_BIT(PWR->MPUCR, PWR_MPUCR_STANDBYWFIL2) == (PWR_MPUCR_STANDBYWFIL2)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 6
  * @rmtoll WKUPFR          WKUPF6          LL_PWR_IsActiveFlag_WU6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU6(void)
{
  return ((READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF6) == (PWR_WKUPFR_WKUPF6)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 5
  * @rmtoll WKUPFR          WKUPF5          LL_PWR_IsActiveFlag_WU5
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU5(void)
{
  return ((READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF5) == (PWR_WKUPFR_WKUPF5)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 4
  * @rmtoll WKUPFR          WKUPF4          LL_PWR_IsActiveFlag_WU4
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU4(void)
{
  return ((READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF4) == (PWR_WKUPFR_WKUPF4)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 3
  * @rmtoll WKUPFR          WKUPF3          LL_PWR_IsActiveFlag_WU3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU3(void)
{
  return ((READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF3) == (PWR_WKUPFR_WKUPF3)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 2
  * @rmtoll WKUPFR          WKUPF2          LL_PWR_IsActiveFlag_WU2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU2(void)
{
  return ((READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF2) == (PWR_WKUPFR_WKUPF2)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 1
  * @rmtoll WKUPFR          WKUPF1          LL_PWR_IsActiveFlag_WU1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU1(void)
{
  return ((READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF1) == (PWR_WKUPFR_WKUPF1)) ? 1UL : 0UL);
}


/**
  * @brief  Clear MCU STANDBY and STOP flags
  * @rmtoll MPUCR   CSSF       LL_PWR_ClearFlag_MPU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_MPU(void)
{
  SET_BIT(PWR->MPUCR, PWR_MPUCR_CSSF);
}

/**
  * @brief  Clear Wake-up Flag 6
  * @rmtoll WKUPCR          WKUPC6         LL_PWR_ClearFlag_WU6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU6(void)
{
  WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC6);
}

/**
  * @brief  Clear Wake-up Flag 5
  * @rmtoll WKUPCR          WKUPC5         LL_PWR_ClearFlag_WU5
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU5(void)
{
  WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC5);
}

/**
  * @brief  Clear Wake-up Flag 4
  * @rmtoll WKUPCR          WKUPC4         LL_PWR_ClearFlag_WU4
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU4(void)
{
  WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC4);
}

/**
  * @brief  Clear Wake-up Flag 3
  * @rmtoll WKUPCR          WKUPC3         LL_PWR_ClearFlag_WU3
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU3(void)
{
  WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC3);
}

/**
  * @brief  Clear Wake-up Flag 2
  * @rmtoll WKUPCR          WKUPC2         LL_PWR_ClearFlag_WU2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU2(void)
{
  WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC2);
}

/**
  * @brief  Clear Wake-up Flag 1
  * @rmtoll WKUPCR          WKUPC1         LL_PWR_ClearFlag_WU1
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU1(void)
{
  WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC1);
}

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup PWR_LL_EF_Init De-initialization function
  * @{
  */
ErrorStatus LL_PWR_DeInit(void);
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(PWR) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32MP13xx_LL_PWR_H */
