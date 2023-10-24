
/* ---------------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#include "main.h"
#include "Board.h"
#include "Buttons.h"



/* ---------------------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#define HOLD1_DELAY_MS					( 2000 )		// [ms]
#define HOLD2_DELAY_MS					( 4000 )		// [ms]


/* ---------------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

ButtonsTypeDef Buttons = {
	.Key1 = {
		.Port = BTN_S1_GPIO_Port,
		.Pin = BTN_S1_Pin,
		.IsNegative = false,
		.Value = false,
		.HoldCounter = 0,
		.State = KEY_NOT_PRESSED,
	},
	.Key2 = {
		.Port = BTN_S2_GPIO_Port,
		.Pin = BTN_S2_Pin,
		.IsNegative = false,
		.Value = false,
		.HoldCounter = 0,
		.State = KEY_NOT_PRESSED,
	},
	.Key3 = {
		.Port = BTN_S3_GPIO_Port,
		.Pin = BTN_S3_Pin,
		.IsNegative = false,
		.Value = false,
		.HoldCounter = 0,
		.State = KEY_NOT_PRESSED,
	},
	.Key4 = {
		.Port = BTN_S4_GPIO_Port,
		.Pin = BTN_S4_Pin,
		.IsNegative = false,
		.Value = false,
		.HoldCounter = 0,
		.State = KEY_NOT_PRESSED,
	},
}; //Buttons



/* ---------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Public Functions ----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

void ButtonsHandler( void ) {

	// set pointer to the first button in the array
	ButtonTypeDef* pButton = (ButtonTypeDef*)&Buttons;

	// a cycle for each button in the <Buttons> structure
	while ( (intptr_t)pButton < ( (intptr_t)&Buttons + sizeof(Buttons) ) ) {

		bool input = HAL_GPIO_ReadPin( pButton->Port, pButton->Pin ) ? true : false;

		pButton->Value = input ^ pButton->IsNegative;

		if ( false == pButton->Value )
		{
			pButton->HoldCounter = 0;
			pButton->State = KEY_NOT_PRESSED;
		} //if
		else
		{
			pButton->HoldCounter++;
			if ( pButton->HoldCounter < HOLD1_DELAY_MS )
			{
				pButton->State = KEY_PRESSED;
			} //if
			else if ( pButton->HoldCounter < HOLD2_DELAY_MS )
			{
				pButton->State = KEY_HOLD_1;
			} //if
			else
			{
				pButton->State = KEY_HOLD_2;
			} //if
		} //else

		pButton++; // inc pointer to the next button's data address
	} //while
} //ButtonsHandler()



/* ---------------------------------------------------------------------------*/
/* Private Functions ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
