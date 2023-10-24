
/* ---------------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#include "main.h"
#include "Board.h"
#include "Buttons.h"
#include "DataExchange.h"
#include "J1939.h"



/* ---------------------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

extern CAN_HandleTypeDef hcan;
extern ButtonsTypeDef Buttons;
extern J1939_PropB_00_TypeDef J1939_PropB_00;
extern J1939_AUXIO2_TypeDef J1939_AUXIO2;



/* ---------------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#define CAN_J1939_TX_PERIOD_MS		( 100 )								// [ms]
#define AUXIO2_FILTER_BANK			( 0 )
#define PROPA_FILTER_BANK			( 1 )



/* ---------------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/**
  * @brief  CAN Heartbeat Structure Definition
  */
typedef struct __CAN_HeartbeatTypeDef
{
	uint32_t const			Timeout;
	uint32_t				Counter;
	__IO bool				IsOperable;
} CAN_HeartbeatTypeDef;


#ifdef DEBUG
/**
  * @brief  CAN Debug Structure Definition
  */
typedef struct __CAN_DebugTypeDef
{
	uint32_t				TxCntr;
	uint32_t				ErrCntr;
	uint32_t				RxCntr;
	uint32_t				RxErrCntr;
} CAN_DebugTypeDef;
#endif



/* ---------------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#define _CONVERT_MS_TO_CAN_CYCLES(X)			(uint32_t)(X) / CAN_J1939_TX_PERIOD_MS



/* ---------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

CAN_HeartbeatTypeDef CAN_Heartbeat = {
	.Timeout = _CONVERT_MS_TO_CAN_CYCLES( 2000 ),
	.Counter = _CONVERT_MS_TO_CAN_CYCLES( 2000 ), // note: down counter mode
	.IsOperable = false,
};

CAN_TxHeaderTypeDef CAN_J1939_PropB_00_Message = { 0 };

uint32_t CAN_MailBoxNumber = CAN_TX_MAILBOX0;

#ifdef DEBUG
CAN_DebugTypeDef CAN_Debug = { 0 };
#endif



/* ---------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* ---------------------------------------------------------------------------*/

void CAN_J1939_PropB_00_Init( void );
int32_t CAN_J1939_PropB_00_Tx( void );



/* ---------------------------------------------------------------------------*/
/* Public Functions ----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

int32_t CAN_Node_Init( void ) {

	HAL_StatusTypeDef HAL_Status;

	HAL_Status = HAL_CAN_Init( &hcan );
	if ( HAL_OK != HAL_Status )
	{
		return -1;
	} //if

	HAL_Status = HAL_CAN_ActivateNotification( &hcan, CAN_IT_TX_MAILBOX_EMPTY
												    | CAN_IT_RX_FIFO0_MSG_PENDING
												    | CAN_IT_RX_FIFO0_FULL
												    | CAN_IT_RX_FIFO0_OVERRUN
												    | CAN_IT_ERROR_WARNING
												    | CAN_IT_ERROR_PASSIVE
												    | CAN_IT_BUSOFF
												    | CAN_IT_LAST_ERROR_CODE
												    | CAN_IT_ERROR );
	if ( HAL_OK != HAL_Status )
	{
		return -1;
	} //if

	// setup filter bank 0 to the J1939 AUXIO2 package ID with undefined priority
	uint32_t filter1 = ( J1939_AUXIO2.ID.PF << 16 ) + ( J1939_AUXIO2.ID.PS << 8 ) + ( J1939_AUXIO2.ID.SourceAddress << 0 );
	CAN_FilterTypeDef filter1_conf = {
		.FilterIdHigh = filter1 >> 13,
		.FilterIdLow = filter1 << 3,
		.FilterMaskIdHigh = 0x00FFFFFF >> 13,
		.FilterMaskIdLow = 0x00FFFFFF << 3,
		.FilterFIFOAssignment = CAN_FILTER_FIFO0,
		.FilterBank = AUXIO2_FILTER_BANK,
		.FilterMode = CAN_FILTERMODE_IDMASK,
		.FilterScale = CAN_FILTERSCALE_32BIT,
		.FilterActivation = CAN_FILTER_ENABLE,
	};
	HAL_Status = HAL_CAN_ConfigFilter( &hcan, &filter1_conf );
	if ( HAL_OK != HAL_Status )
	{
		return -1;
	} //if

	HAL_Status = HAL_CAN_Start( &hcan );
	if ( HAL_OK != HAL_Status )
	{
		return -1;
	} //if

	_SET_CAN_NORMAL_MODE; // switch CAN driver to the normal mode

	CAN_J1939_PropB_00_Init();

	return 0;
} //CAN_Node_Init()



void CAN_J1939_Step( void )
{
	static uint32_t CAN_cycle = 0;

	if ( ++CAN_cycle > CAN_J1939_TX_PERIOD_MS )
	{
		CAN_cycle = 0;

		CAN_J1939_PropB_00_Tx();

		// communication "heartbeat" check
		if ( CAN_Heartbeat.Counter != 0 )
		{
			CAN_Heartbeat.Counter--;
			CAN_Heartbeat.IsOperable = true;
		} //if
		else
		{
			CAN_Heartbeat.IsOperable = false;
			DisableLEDs();
		} //else
	} //if
} //CAN_J1939_Step()



/* ---------------------------------------------------------------------------*/
/* Private Functions ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

void CAN_J1939_PropB_00_Init( void )
{
	J1939_PropB_00_TypeDef* pPGN = &J1939_PropB_00;

	// package header init
	CAN_J1939_PropB_00_Message.ExtId = ( pPGN->ID.Priority << 26 ) + ( pPGN->ID.PF << 16 ) + ( pPGN->ID.PS << 8 ) + ( pPGN->ID.SourceAddress << 0 );
	CAN_J1939_PropB_00_Message.IDE = CAN_ID_EXT;
	CAN_J1939_PropB_00_Message.RTR = CAN_RTR_DATA;
	CAN_J1939_PropB_00_Message.DLC = 8;
	CAN_J1939_PropB_00_Message.TransmitGlobalTime = DISABLE;

} //CAN_J1939_PropB_00_Init()



int32_t CAN_J1939_PropB_00_Tx( void )
{
	if ( 0 == HAL_CAN_IsTxMessagePending( &hcan, CAN_MailBoxNumber ) )
	{
		J1939_PropB_00_TypeDef* pPGN = &J1939_PropB_00;

		// updating package data bytes
		pPGN->Key1 = Buttons.Key1.State;
		pPGN->Key2 = Buttons.Key2.State;
		pPGN->Key3 = Buttons.Key3.State;
		pPGN->Key4 = Buttons.Key4.State;

		HAL_StatusTypeDef HAL_Status = HAL_CAN_AddTxMessage( &hcan, &CAN_J1939_PropB_00_Message, pPGN->DataBytes, &CAN_MailBoxNumber );
		if ( HAL_OK == HAL_Status )
		{
			return 0;
		} //if
	} //if
	return -1;
} //CAN_J1939_PropB_00_Tx()



void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan)
{
	// add actions if necessary...
#ifdef DEBUG
	CAN_Debug.TxCntr++;
#endif
}



void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan) {

	if ( HAL_CAN_ERROR_TX_ALST0 == ( hcan->ErrorCode & HAL_CAN_ERROR_TX_ALST0 ) )
	{
		CAN_J1939_PropB_00_Tx();
	} //if
	else if ( HAL_CAN_ERROR_TX_TERR0 == ( hcan->ErrorCode & HAL_CAN_ERROR_TX_TERR0 ) )
	{
		CAN_J1939_PropB_00_Tx();
	} //if
	else if ( HAL_CAN_ERROR_ACK == ( hcan->ErrorCode & HAL_CAN_ERROR_ACK ) )
	{
		// add actions if necessary...
	} //if
	else
	{
		; //no actions required...
	} //else

	HAL_CAN_ResetError( hcan );

#ifdef DEBUG
	CAN_Debug.ErrCntr++;
#endif
}



void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {

#ifdef DEBUG
	CAN_Debug.RxCntr++;
#endif

	CAN_RxHeaderTypeDef RxHeader = { 0 };
	uint8_t data[8];
	HAL_StatusTypeDef HAL_status = HAL_CAN_GetRxMessage( hcan, CAN_RX_FIFO0, &RxHeader, data );
	if ( HAL_OK != HAL_status)
	{
		return;
	} //if

	switch ( RxHeader.FilterMatchIndex )
	{

	case AUXIO2_FILTER_BANK :
	{
		*(uint64_t*)J1939_AUXIO2.DataBytes = *(uint64_t*)data;
		break;
	} //case

	default :
	{
#ifdef DEBUG
		CAN_Debug.RxErrCntr++;
#endif
		break;
	} //default

	} //switch

	// update data with received CAN message
	UpdateData();

	// reset the "heartbeat" counter
	CAN_Heartbeat.Counter = CAN_Heartbeat.Timeout;
}
