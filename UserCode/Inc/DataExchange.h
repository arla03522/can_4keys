
#ifndef USERCODE_DATAEXCHANGE_H_
#define USERCODE_DATAEXCHANGE_H_



/* ---------------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/


#include "J1939.h"



/* ---------------------------------------------------------------------------*/
/* Defines -------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#define J1939_ADDRESS				( 256 )					// Source Address

#define PROPB_00_PF					( 255 )					// [PDU Format] SAE J1939 PropB = Proprietary B
#define PROPB_00_PS					( 0 )					// [PDU Specific] SAE J1939 PropB_00 = Proprietary B, 0 entry
#define PROPB_00_PRIO				( 6UL )					// Message Priority ( available values 0 .. 7, default priority is 6 )

#define AUXIO2_PF					( 167 )					// [PDU Format] SAE J1939 AUXIO2 = Auxiliary Input/Output Status 2,
#define AUXIO2_PS					J1939_ADDRESS			// [PDU Specific] Corresponds to destination address
#define AUXIO2_PRIO					( 6UL )					// Message Priority ( available values 0 .. 7, default priority is 6 )
#define AUXIO2_SA					( 3UL )					// Transmitter J1939 Source Address

#if ( J1939_ADDRESS > 255 )
#error Incorrect CAN J1939 Source Address
#endif
#if ( ( ( PROPB_00_PF << 8 ) + PROPB_00_PS ) > 524287 )
#error Incorrect CAN J1939 Parameter Group Number
#endif
#if ( PROPB_00_PRIO > 7 )
#error Incorrect CAN J1939 Priority
#endif
#if ( ( ( AUXIO2_PF << 8 ) + AUXIO2_PS ) > 524287 )
#error Incorrect CAN J1939 Parameter Group Number
#endif
#if ( AUXIO2_SA > 255 )
#error Incorrect CAN J1939 Source Address
#endif
#if ( AUXIO2_PRIO > 7 )
#error Incorrect CAN J1939 Priority
#endif



/* ---------------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/**
  * @brief  J1939 Message ID Structure Definition
  */
typedef struct __J1939_ID_TypeDef
{
	uint32_t const						PF;					/*!< PDU Format */

	uint32_t const						PS;					/*!< PDU Specific */

	uint32_t const						Priority;			/*!< Priority */

	uint32_t const						SourceAddress;		/*!< Source Address */

} J1939_ID_TypeDef;



/**
  * @brief  J1939 "Proprietary B" Message Structure Definition
  */
typedef struct __J1939_PropB_00_TypeDef
{
	J1939_ID_TypeDef						ID;

	union {
		uint8_t								DataBytes[8];
		struct {
			struct {
				KEYCAN_ButtonStateTypeDef	Key1				: 2;
				uint8_t						ReservedBits1		: 2;
				KEYCAN_ButtonStateTypeDef	Key2				: 2;
				uint8_t						ReservedBits2		: 2;
			};
			struct {
				KEYCAN_ButtonStateTypeDef	Key3				: 2;
				uint8_t						ReservedBits3		: 2;
				KEYCAN_ButtonStateTypeDef	Key4				: 2;
				uint8_t						ReservedBits4		: 2;
			};
			uint8_t							ReservedByte3;
			uint8_t							ReservedByte4;
			uint8_t							ReservedByte5;
			uint8_t							ReservedByte6;
			uint8_t							ReservedByte7;
			uint8_t							ReservedByte8;
		};
	};
} J1939_PropB_00_TypeDef;



/**
  * @brief  J1939 "Auxiliary Input/Output Status 2" Message Structure Definition
  */
typedef struct __J1939_AUXIO2_TypeDef
{
	J1939_ID_TypeDef						ID;

	union {
		uint8_t								DataBytes[8];
		struct {
			struct {
				bool						Key1_R				: 1;
				bool						Key1_G				: 1;
				bool						Key1_B				: 1;
				uint8_t											: 0;
			};
			struct {
				bool						Key2_R				: 1;
				bool						Key2_G				: 1;
				bool						Key2_B				: 1;
				uint8_t											: 0;
			};
			uint8_t							ReservedByte3;
			uint8_t							ReservedByte4;
			struct {
				bool						Key3_R				: 1;
				bool						Key3_G				: 1;
				bool						Key3_B				: 1;
				uint8_t											: 0;
			};
			struct {
				bool						Key4_R				: 1;
				bool						Key4_G				: 1;
				bool						Key4_B				: 1;
				uint8_t											: 0;
			};
			uint8_t							ReservedByte7;
			uint8_t							BacklightIntensity;
		};
	};
} J1939_AUXIO2_TypeDef;



/* ---------------------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
/* ---------------------------------------------------------------------------*/

void UpdateData( void );
void DisableLEDs( void );



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


