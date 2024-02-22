/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    etzpc.c
  * @brief   This file provides code for the configuration
  *          of the ETZPC instances.
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
#include "etzpc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

ETZPC_TypeDef ETZPCx;
uint32_t size;

/* ETZPC init function */
void MX_ETZPC_Init(void)
{

  /* USER CODE BEGIN ETZPC_Init 0 */

  /* USER CODE END ETZPC_Init 0 */

  /* USER CODE BEGIN ETZPC_Init 1 */

  /* USER CODE END ETZPC_Init 1 */
  HAL_ETZPC_SetSecureSysRamSize(ETZPC, 0x1000);
  /* USER CODE BEGIN ETZPC_Init 2 */

  /* USER CODE END ETZPC_Init 2 */

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
