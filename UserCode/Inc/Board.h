
#ifndef USERCODE_BOARD_H_
#define USERCODE_BOARD_H_

/* ---------------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#include "main.h"



/* ---------------------------------------------------------------------------*/
/* Defines -------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#define CAN_DRIVER_TJA1051
//#define CAN_DRIVER_TJA1042



/* ---------------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#define _GET_BTN_S1_STATE		HAL_GPIO_ReadPin(BTN_S1_GPIO_Port, BTN_S1_Pin)									// Read Digital Input Button S1
#define _GET_BTN_S2_STATE		HAL_GPIO_ReadPin(BTN_S3_GPIO_Port, BTN_S2_Pin)									// Read Digital Input Button S2
#define _GET_BTN_S3_STATE		HAL_GPIO_ReadPin(BTN_S4_GPIO_Port, BTN_S3_Pin)									// Read Digital Input Button S3
#define _GET_BTN_S4_STATE		HAL_GPIO_ReadPin(BTN_S5_GPIO_Port, BTN_S4_Pin)									// Read Digital Input Button S4

#define _ENABLE_BTNS			HAL_GPIO_WritePin(BTNS_EN_GPIO_Port, BTNS_EN_Pin, GPIO_PIN_SET)					// Enable Digital Output Low Power High Side
#define _DISABLE_BTNS			HAL_GPIO_WritePin(BTNS_EN_GPIO_Port, BTNS_EN_Pin, GPIO_PIN_RESET)				// Disable Digital Output Low Power High Side

#define _ENABLE_LATCH			HAL_GPIO_WritePin(REG_LE_GPIO_Port, REG_LE_Pin, GPIO_PIN_SET)					// Enable Digital Output Low Power Low Side
#define _DISABLE_LATCH			HAL_GPIO_WritePin(REG_LE_GPIO_Port, REG_LE_Pin, GPIO_PIN_RESET)					// Disable Digital Output Low Power Low Side

#ifdef CAN_DRIVER_TJA1051
#define _SET_CAN_NORMAL_MODE	HAL_GPIO_WritePin( CAN_MODE_GPIO_Port, CAN_MODE_Pin, GPIO_PIN_SET )				// Enable Digital Output Low Power High Side CAN driver pin S
#define _SET_CAN_SILENT_MODE	HAL_GPIO_WritePin( CAN_MODE_GPIO_Port, CAN_MODE_Pin, GPIO_PIN_RESET )			// Disable Digital Output Low Power High Side CAN driver pin S
#endif
#ifdef CAN_DRIVER_TJA1042
#define _SET_CAN_NORMAL_MODE	HAL_GPIO_WritePin( CAN_MODE_GPIO_Port, CAN_MODE_Pin, GPIO_PIN_RESET )			// Enable Digital Output Low Power High Side CAN driver pin S
#define _SET_CAN_STANDBY_MODE	HAL_GPIO_WritePin( CAN_MODE_GPIO_Port, CAN_MODE_Pin, GPIO_PIN_SET )				// Disable Digital Output Low Power High Side CAN driver pin S
#endif



/* ---------------------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#endif /* USERCODE_BOARD_H_ */
