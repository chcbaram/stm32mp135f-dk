/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32mp13xx_it.h
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
 ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32MP13xx_IT_H
#define __STM32MP13xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif


/* Exported functions prototypes ---------------------------------------------*/
void SysTick_Handler(void);
void SGI0_IRQHandler(void);
void SGI1_IRQHandler(void);
void SGI2_IRQHandler(void);
void SGI3_IRQHandler(void);
void SGI4_IRQHandler(void);
void SGI5_IRQHandler(void);
void SGI6_IRQHandler(void);
void SGI7_IRQHandler(void);
void SGI8_IRQHandler(void);
void SGI9_IRQHandler(void);
void SGI10_IRQHandler(void);
void SGI11_IRQHandler(void);
void SGI12_IRQHandler(void);
void SGI13_IRQHandler(void);
void SGI14_IRQHandler(void);
void SGI15_IRQHandler(void);
void RCC_WAKEUP_IRQHandler(void);


#ifdef __cplusplus
}
#endif

#endif /* __STM32MP13xx_IT_H */
