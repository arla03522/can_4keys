
/* ---------------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#include "main.h"
#include "Board.h"
#include "LEDs.h"



/* ---------------------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

extern SPI_HandleTypeDef hspi1;
extern TIM_HandleTypeDef htim1;



/* ---------------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

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

LEDsTypeDef LEDs[BTNS_AMOUNT];
volatile uint8_t LEDsBrightness = 255;



/* ---------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Public Functions ----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

void LEDsHandler( void ) {

	static uint32_t scan_index = 0;

	HAL_StatusTypeDef status;
	status = HAL_SPI_Transmit( &hspi1, (uint8_t*)&LEDs[scan_index], 1, 1000 );

	switch ( scan_index ) {

	case 0 :
	{
		HAL_GPIO_WritePin(OUT_K1_GPIO_Port, OUT_K1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(OUT_K2_GPIO_Port, OUT_K2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(OUT_K3_GPIO_Port, OUT_K3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(OUT_K4_GPIO_Port, OUT_K4_Pin, GPIO_PIN_SET);
	} //case

	case 1 :
	{
		HAL_GPIO_WritePin(OUT_K1_GPIO_Port, OUT_K1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(OUT_K2_GPIO_Port, OUT_K2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(OUT_K3_GPIO_Port, OUT_K3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(OUT_K4_GPIO_Port, OUT_K4_Pin, GPIO_PIN_SET);
	} //case

	case 2 :
	{
		HAL_GPIO_WritePin(OUT_K1_GPIO_Port, OUT_K1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(OUT_K2_GPIO_Port, OUT_K2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(OUT_K3_GPIO_Port, OUT_K3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(OUT_K4_GPIO_Port, OUT_K4_Pin, GPIO_PIN_SET);
	} //case

	case 3 :
	{
		HAL_GPIO_WritePin(OUT_K1_GPIO_Port, OUT_K1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(OUT_K2_GPIO_Port, OUT_K2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(OUT_K3_GPIO_Port, OUT_K3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(OUT_K4_GPIO_Port, OUT_K4_Pin, GPIO_PIN_RESET);
	} //case

	default :
	{
		scan_index = 0;
		break;
	} //default

	} //switch

	_ENABLE_LATCH;
	_DISABLE_LATCH;

	if ( ++scan_index > 4 )
	{
		scan_index = 0;
	} //if

	// update LEDs brightness
	htim1.Instance->CCR1 = LEDsBrightness;

} //LEDsHandler()



/* ---------------------------------------------------------------------------*/
/* Private Functions ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
