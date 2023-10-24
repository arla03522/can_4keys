
/* ---------------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#include "main.h"
#include "LEDs.h"
#include "DataExchange.h"



/* ---------------------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

extern LEDsTypeDef LEDs[BTNS_AMOUNT];
extern volatile uint8_t LEDsBrightness;



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

J1939_PropB_00_TypeDef J1939_PropB_00 = {
	.ID = {
		.PF = PROPB_00_PF,
		.PS = PROPB_00_PS,
		.Priority = PROPB_00_PRIO,
		.SourceAddress = J1939_ADDRESS,
	},
	.Key1 = KEY_NOT_PRESSED,
	.ReservedBits1 = J1939_NOT_AVAILABLE,
	.Key2 = KEY_NOT_PRESSED,
	.ReservedBits2 = J1939_NOT_AVAILABLE,
	.Key3 = KEY_NOT_PRESSED,
	.ReservedBits3 = J1939_NOT_AVAILABLE,
	.Key4 = KEY_NOT_PRESSED,
	.ReservedBits4 = J1939_NOT_AVAILABLE,
	.ReservedByte3 = 0xFF,
	.ReservedByte4 = 0xFF,
	.ReservedByte5 = 0xFF,
	.ReservedByte6 = 0xFF,
	.ReservedByte7 = 0xFF,
	.ReservedByte8 = 0xFF,
};

J1939_AUXIO2_TypeDef J1939_AUXIO2 = {
	.ID = {
		.PF = AUXIO2_PF,
		.PS = AUXIO2_PS,
		.Priority = AUXIO2_PRIO,
		.SourceAddress = AUXIO2_SA,
	},
};



/* ---------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Public Functions ----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

void UpdateData( void ) {

	LEDs[KEY1].Red = J1939_AUXIO2.Key1_R;
	LEDs[KEY1].Green = J1939_AUXIO2.Key1_G;
	LEDs[KEY1].Blue = J1939_AUXIO2.Key1_B;

	LEDs[KEY1].Red = J1939_AUXIO2.Key2_R;
	LEDs[KEY2].Green = J1939_AUXIO2.Key2_G;
	LEDs[KEY2].Blue = J1939_AUXIO2.Key2_B;

	LEDs[KEY3].Red = J1939_AUXIO2.Key3_R;
	LEDs[KEY3].Green = J1939_AUXIO2.Key3_G;
	LEDs[KEY3].Blue = J1939_AUXIO2.Key3_B;

	LEDs[KEY4].Red = J1939_AUXIO2.Key4_R;
	LEDs[KEY4].Green = J1939_AUXIO2.Key4_G;
	LEDs[KEY4].Blue = J1939_AUXIO2.Key4_B;

	if ( J1939_AUXIO2.BacklightIntensity < 255 )
	{
		LEDsBrightness = J1939_AUXIO2.BacklightIntensity;
	} //if
	else
	{
		LEDsBrightness = 0;
	} //else
} //UpdateData()



void DisableLEDs( void ) {

	*(uint64_t*)J1939_AUXIO2.DataBytes = 0;
	LEDs[KEY1].BitsArray = 0;
	LEDs[KEY2].BitsArray = 0;
	LEDs[KEY3].BitsArray = 0;
	LEDs[KEY4].BitsArray = 0;
	LEDsBrightness = 0;
} //DisableLEDs()



/* ---------------------------------------------------------------------------*/
/* Private Functions ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
