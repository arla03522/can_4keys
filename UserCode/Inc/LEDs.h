
#ifndef USERCODE_INC_LEDS_H_
#define USERCODE_INC_LEDS_H_



/* ---------------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Defines -------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#define KEY1							0
#define KEY2							1
#define KEY3							2
#define KEY4							3
#define BTNS_AMOUNT						4



/* ---------------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/**
  * @brief  LEDs Structure Definition
  */
typedef struct __LEDsTypeDef
{
	union {
		uint8_t							BitsArray;
		struct {
			bool						Red			: 1;	/*!< Backlight Red LED */
			bool						Green		: 1;	/*!< Backlight Green LED */
			bool						Blue		: 1;	/*!< Backlight Blue LED */
			uint8_t									: 0;	/*!< Unused */
		};
	};
} LEDsTypeDef;



/* ---------------------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
/* ---------------------------------------------------------------------------*/

void LEDsHandler( void );



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

#endif /* USERCODE_INC_LEDS_H_ */
