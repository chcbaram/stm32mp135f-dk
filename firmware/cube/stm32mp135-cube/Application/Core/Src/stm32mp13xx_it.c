/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32mp13xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32mp13xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern SD_HandleTypeDef hsd1;
extern DMA_HandleTypeDef hdma_uart4_rx;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/**
  * @brief This function handles Software Generated Interrupt  0.
  */
void SGI0_IRQHandler(void)
{
  /* USER CODE BEGIN SGI0_IRQn 0 */

  /* USER CODE END SGI0_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_SGI0_IRQn 0 */
    /* USER CODE END W1_SGI0_IRQn 0 */
  }
}

/**
  * @brief This function handles Software Generated Interrupt  1.
  */
void SGI1_IRQHandler(void)
{
  /* USER CODE BEGIN SGI1_IRQn 0 */

  /* USER CODE END SGI1_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_SGI1_IRQn 0 */
    /* USER CODE END W1_SGI1_IRQn 0 */
  }
}

/**
  * @brief This function handles Software Generated Interrupt  2.
  */
void SGI2_IRQHandler(void)
{
  /* USER CODE BEGIN SGI2_IRQn 0 */

  /* USER CODE END SGI2_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_SGI2_IRQn 0 */
    /* USER CODE END W1_SGI2_IRQn 0 */
  }
}

/**
  * @brief This function handles Software Generated Interrupt  3.
  */
void SGI3_IRQHandler(void)
{
  /* USER CODE BEGIN SGI3_IRQn 0 */

  /* USER CODE END SGI3_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_SGI3_IRQn 0 */
    /* USER CODE END W1_SGI3_IRQn 0 */
  }
}

/**
  * @brief This function handles Software Generated Interrupt  4.
  */
void SGI4_IRQHandler(void)
{
  /* USER CODE BEGIN SGI4_IRQn 0 */

  /* USER CODE END SGI4_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_SGI4_IRQn 0 */
    /* USER CODE END W1_SGI4_IRQn 0 */
  }
}

/**
  * @brief This function handles Software Generated Interrupt  5.
  */
void SGI5_IRQHandler(void)
{
  /* USER CODE BEGIN SGI5_IRQn 0 */

  /* USER CODE END SGI5_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_SGI5_IRQn 0 */
    /* USER CODE END W1_SGI5_IRQn 0 */
  }
}

/**
  * @brief This function handles Software Generated Interrupt  6.
  */
void SGI6_IRQHandler(void)
{
  /* USER CODE BEGIN SGI6_IRQn 0 */

  /* USER CODE END SGI6_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_SGI6_IRQn 0 */
    /* USER CODE END W1_SGI6_IRQn 0 */
  }
}

/**
  * @brief This function handles Software Generated Interrupt  7.
  */
void SGI7_IRQHandler(void)
{
  /* USER CODE BEGIN SGI7_IRQn 0 */

  /* USER CODE END SGI7_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_SGI7_IRQn 0 */
    /* USER CODE END W1_SGI7_IRQn 0 */
  }
}

/**
  * @brief This function handles Software Generated Interrupt  8.
  */
void SGI8_IRQHandler(void)
{
  /* USER CODE BEGIN SGI8_IRQn 0 */

  /* USER CODE END SGI8_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_SGI8_IRQn 0 */
    /* USER CODE END W1_SGI8_IRQn 0 */
  }
}

/**
  * @brief This function handles Software Generated Interrupt  9.
  */
void SGI9_IRQHandler(void)
{
  /* USER CODE BEGIN SGI9_IRQn 0 */

  /* USER CODE END SGI9_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_SGI9_IRQn 0 */
    /* USER CODE END W1_SGI9_IRQn 0 */
  }
}

/**
  * @brief This function handles Software Generated Interrupt  10.
  */
void SGI10_IRQHandler(void)
{
  /* USER CODE BEGIN SGI10_IRQn 0 */

  /* USER CODE END SGI10_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_SGI10_IRQn 0 */
    /* USER CODE END W1_SGI10_IRQn 0 */
  }
}

/**
  * @brief This function handles Software Generated Interrupt  11.
  */
void SGI11_IRQHandler(void)
{
  /* USER CODE BEGIN SGI11_IRQn 0 */

  /* USER CODE END SGI11_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_SGI11_IRQn 0 */
    /* USER CODE END W1_SGI11_IRQn 0 */
  }
}

/**
  * @brief This function handles Software Generated Interrupt  12.
  */
void SGI12_IRQHandler(void)
{
  /* USER CODE BEGIN SGI12_IRQn 0 */

  /* USER CODE END SGI12_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_SGI12_IRQn 0 */
    /* USER CODE END W1_SGI12_IRQn 0 */
  }
}

/**
  * @brief This function handles Software Generated Interrupt  13.
  */
void SGI13_IRQHandler(void)
{
  /* USER CODE BEGIN SGI13_IRQn 0 */

  /* USER CODE END SGI13_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_SGI13_IRQn 0 */
    /* USER CODE END W1_SGI13_IRQn 0 */
  }
}

/**
  * @brief This function handles Software Generated Interrupt  14.
  */
void SGI14_IRQHandler(void)
{
  /* USER CODE BEGIN SGI14_IRQn 0 */

  /* USER CODE END SGI14_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_SGI14_IRQn 0 */
    /* USER CODE END W1_SGI14_IRQn 0 */
  }
}

/**
  * @brief This function handles Software Generated Interrupt  15.
  */
void SGI15_IRQHandler(void)
{
  /* USER CODE BEGIN SGI15_IRQn 0 */

  /* USER CODE END SGI15_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_SGI15_IRQn 0 */
    /* USER CODE END W1_SGI15_IRQn 0 */
  }
}

/******************************************************************************/
/* STM32MP13xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32mp13xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 stream0 global interrupt.
  */
void DMA1_Stream0_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream0_IRQn 0 */

  /* USER CODE END DMA1_Stream0_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_uart4_rx);
  /* USER CODE BEGIN DMA1_Stream0_IRQn 1 */

  /* USER CODE END DMA1_Stream0_IRQn 1 */
}

/**
  * @brief This function handles SDMMC1 global interrupt.
  */
void SDMMC1_IRQHandler(void)
{
  /* USER CODE BEGIN SDMMC1_IRQn 0 */

  /* USER CODE END SDMMC1_IRQn 0 */
  HAL_SD_IRQHandler(&hsd1);
  /* USER CODE BEGIN SDMMC1_IRQn 1 */

  /* USER CODE END SDMMC1_IRQn 1 */
}

/**
  * @brief This function handles RCC wake-up interrupt.
  */
void RCC_WAKEUP_IRQHandler(void)
{
  /* USER CODE BEGIN RCC_WAKEUP_IRQn 0 */

  /* USER CODE END RCC_WAKEUP_IRQn 0 */
  HAL_RCC_WAKEUP_IRQHandler();
  /* USER CODE BEGIN RCC_WAKEUP_IRQn 1 */

  /* USER CODE END RCC_WAKEUP_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
