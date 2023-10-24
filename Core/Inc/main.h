/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

typedef uint32_t __istate_t;
typedef uint8_t bool;
#define true	(1)
#define false	(0)

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BTNS_EN_Pin GPIO_PIN_0
#define BTNS_EN_GPIO_Port GPIOA
#define BTN_S1_Pin GPIO_PIN_1
#define BTN_S1_GPIO_Port GPIOA
#define BTN_S2_Pin GPIO_PIN_2
#define BTN_S2_GPIO_Port GPIOA
#define BTN_S3_Pin GPIO_PIN_3
#define BTN_S3_GPIO_Port GPIOA
#define BTN_S4_Pin GPIO_PIN_4
#define BTN_S4_GPIO_Port GPIOA
#define REG_CLK_Pin GPIO_PIN_5
#define REG_CLK_GPIO_Port GPIOA
#define REG_SDI_Pin GPIO_PIN_7
#define REG_SDI_GPIO_Port GPIOA
#define REG_LE_Pin GPIO_PIN_0
#define REG_LE_GPIO_Port GPIOB
#define REG_OE_Pin GPIO_PIN_8
#define REG_OE_GPIO_Port GPIOA
#define CAN_MODE_Pin GPIO_PIN_10
#define CAN_MODE_GPIO_Port GPIOA
#define OUT_K4_Pin GPIO_PIN_4
#define OUT_K4_GPIO_Port GPIOB
#define OUT_K3_Pin GPIO_PIN_5
#define OUT_K3_GPIO_Port GPIOB
#define OUT_K2_Pin GPIO_PIN_6
#define OUT_K2_GPIO_Port GPIOB
#define OUT_K1_Pin GPIO_PIN_7
#define OUT_K1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
