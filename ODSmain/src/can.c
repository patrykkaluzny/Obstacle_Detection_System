#include <flags.h>
#include "can.h"
#include "gpio.h"
#include "tim.h"
#include "main.h"
#include "CAN2flags.h"
#include "initSystemFunctions.h"
#include "structures.h"
#include "functions.h"

//can variables
CAN_InitTypeDef CAN_InitStructure;
CAN_FilterInitTypeDef CAN_FilterInitStructure;
CanRxMsg CAN1_rFrame;
CanRxMsg CAN2_rFrame;
int CAN1_mailbox;
int CAN2_mailbox;

//can buffers
volatile typ_CANTxBuffer CAN1TxBuffer;
volatile typ_CANTxBuffer CAN2TxBuffer;

//data structures
extern typ_ODSmainData ODSmainData;

/*************************** CAN_Conf *****************************
 * Function Name  : CAN_Conf
 * Description    : Configuration CAN1.
 * Input          : None
 * Output         : None
 * Return         : None
 ********************************************************************/
void CAN_Conf(void) {
	// periphery initialization
	//CAN1

	CAN_DeInit(CAN1);
	CAN_StructInit(&CAN_InitStructure);
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_ABOM = DISABLE;
	CAN_InitStructure.CAN_AWUM = DISABLE;
	CAN_InitStructure.CAN_NART = DISABLE;
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TXFP = ENABLE;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; //CAN_Mode_Silent;//CAN_Mode_Normal;//CAN_Mode_LoopBack;
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1 = CAN_BS1_12tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
	CAN_InitStructure.CAN_Prescaler = 3;
	CAN_Init(CAN1, &CAN_InitStructure);

	//CAN2

	CAN_DeInit(CAN2);
	//CAN_StructInit(&CAN_InitStructure);
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_ABOM = DISABLE;
	CAN_InitStructure.CAN_AWUM = DISABLE;
	CAN_InitStructure.CAN_NART = DISABLE;
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TXFP = ENABLE;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; //CoAN_Mode_Silent;//CAN_Mode_Normal;//CAN_Mode_LoopBack;
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1 = CAN_BS1_12tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
	CAN_InitStructure.CAN_Prescaler = 3;
	CAN_Init(CAN2, &CAN_InitStructure);

	//filters configuration
	//CAN1

	CAN_ClearFlag(CAN1, CAN_FLAG_FMP0);
	CAN_FilterInitStructure.CAN_FilterNumber = 0;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_16bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);

	//CAN2

	CAN_ClearFlag(CAN2, CAN_FLAG_FMP0);
	CAN_FilterInitStructure.CAN_FilterNumber = 14;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_16bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	CAN_SlaveStartBank(14);



	/* Transmit Structure preparation */

	//CAN1

	CAN1_rFrame.StdId = 0x01;
	CAN1_rFrame.ExtId = 0x01;
	CAN1_rFrame.IDE = CAN_Id_Standard;
	CAN1_rFrame.RTR = CAN_RTR_DATA;
	CAN1_rFrame.DLC = 8;
	CAN1_rFrame.FMI = 0x00;
	for (int k = 0; k < 8; k++) {
				CAN1_rFrame.Data[k] = 0;
			}

	/* Enable FIFO 0 message pending Interrupt */
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	CAN_ITConfig(CAN1, CAN_IT_FMP1, ENABLE);

	//CAN2

	CAN2_rFrame.StdId = 0x01;
	CAN2_rFrame.ExtId = 0x01;
	CAN2_rFrame.IDE = CAN_Id_Standard;
	CAN2_rFrame.RTR = CAN_RTR_DATA;
	CAN2_rFrame.DLC = 8;
	CAN2_rFrame.FMI = 0x00;
	for (int k = 0; k < 8; k++) {
			CAN2_rFrame.Data[k] = 0;
		}

	/* Enable FIFO 0 message pending Interrupt */
	CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);
	CAN_ITConfig(CAN2, CAN_IT_FMP1, ENABLE);
}

void CAN1_SendFrameWithBuffer(uint32_t CANStdId, uint32_t *CANData1, uint32_t *CANData2)
{
	// temporary frame variable
	CanTxMsg tempFrame;

	// filling frame
	tempFrame.ExtId=0x01;
	tempFrame.StdId= CANStdId;
	tempFrame.IDE= CAN_ID_STD;
	tempFrame.RTR=CAN_RTR_DATA;
	tempFrame.DLC=8;

	// date copying
	*(uint32_t*)(&tempFrame.Data[0]) = *CANData1;
	*(uint32_t*)(&tempFrame.Data[4]) = *CANData2;

	// try to send frame
	CAN1_mailbox=CAN_Transmit(CAN1, &tempFrame);

	if (_CAN1_TIM_RESEND->CR1 & TIM_CR1_CEN) {
		CAN1_Add2Buffer(&tempFrame);
		if (CAN1TxBuffer.sFrameBufferOVF) {
			SetBits(ODSmainData.errorFlagPart1,_CAN1_BUFFER_OVF);
		}
	}
	else {
		// check if its sended
		if (CAN1_mailbox == CAN_TxStatus_NoMailBox) {
			// if mailboxes are occupied
			CAN1_Add2Buffer(&tempFrame);
			if (CAN1TxBuffer.sFrameBufferOVF) {
				SetBits(ODSmainData.errorFlagPart1,_CAN1_BUFFER_OVF);
			}
		}
	}
}
void CAN2_SendFrameWithBuffer(uint32_t CANStdId, uint32_t *CANData1, uint32_t *CANData2)
{
	// temporary frame variable
	CanTxMsg tempFrame;

	// filling frame
	tempFrame.ExtId=0x01;
	tempFrame.StdId= CANStdId;
	tempFrame.IDE= CAN_ID_STD;
	tempFrame.RTR=CAN_RTR_DATA;
	tempFrame.DLC=8;

	// date copying
	Double_U32_to_U8_Array(tempFrame.Data,CANData1,CANData2);

	// try to send frame
	CAN2_mailbox=CAN_Transmit(CAN2, &tempFrame);

	if (_CAN2_TIM_RESEND->CR1 & TIM_CR1_CEN) {
		CAN2_Add2Buffer(&tempFrame);
		if (CAN2TxBuffer.sFrameBufferOVF) {
			SetBits(ODSmainData.errorFlagPart1,_CAN2_BUFFER_OVF);
		}
	} else {
		// check if its sended
		if (CAN2_mailbox == CAN_TxStatus_NoMailBox) {
			// if mailboxes are occupied
			CAN2_Add2Buffer(&tempFrame);
			if (CAN2TxBuffer.sFrameBufferOVF) {
				SetBits(ODSmainData.errorFlagPart1,_CAN2_BUFFER_OVF);
			}
		}
	}
}




u8 CAN1_ResendFrame(volatile CanTxMsg *CANPackage)
{
	u8 result = CAN_Transmit(CAN1, CANPackage);
	return result;
}
u8 CAN2_ResendFrame(volatile CanTxMsg *CANPackage)
{
	u8 result = CAN_Transmit(CAN2, CANPackage);
	return result;
}

u8 CAN1_Add2Buffer(CanTxMsg *CANPackage)
{
	//check if buffer is overflow
	if (!CAN1_CheckOverflow()) {
		// add frame to buffer
		CAN1TxBuffer.sFrameBuffer[CAN1TxBuffer.sFrameBufferHead] = *CANPackage;
		// counter increment
		CAN1TxBuffer.sFrameBufferHead++;
		if (CAN1TxBuffer.sFrameBufferHead >= _CAN_TX_BUFFER_SIZE)
		{
			CAN1TxBuffer.sFrameBufferHead = 0;
		}
		// enable timer14
		TIM_Cmd(TIM14, ENABLE);
		return 1;
	} else {
		// set error flag
		CAN1TxBuffer.sFrameBufferOVF = 1;
		SetBits(ODSmainData.errorFlagPart1,_CAN1_BUFFER_OVF);
		return 0;
	}
}
u8 CAN2_Add2Buffer(CanTxMsg *CANPackage)
{
	//check if buffer is overflow
	if (!CAN2_CheckOverflow()) {
		// add frame to buffer
		CAN2TxBuffer.sFrameBuffer[CAN2TxBuffer.sFrameBufferHead] = *CANPackage;
		// counter increment
		CAN2TxBuffer.sFrameBufferHead++;
		if (CAN2TxBuffer.sFrameBufferHead >= _CAN_TX_BUFFER_SIZE)
		{
			CAN2TxBuffer.sFrameBufferHead = 0;
		}
		// enable timer13
		TIM_Cmd(TIM13, ENABLE);
		return 1;
	} else {
		// set error flag
		CAN2TxBuffer.sFrameBufferOVF = 1;
		SetBits(ODSmainData.errorFlagPart1,_CAN2_BUFFER_OVF);
		return 0;
	}
}
u8 CAN1_CheckOverflow(void)
{
	// | | |T|x|x|x|H| |
	if(CAN1TxBuffer.sFrameBufferTail != 0)
	{
		// |x|H|T|x|x|x|x|x|
		if(CAN1TxBuffer.sFrameBufferHead == CAN1TxBuffer.sFrameBufferTail-1)
		{
			return 1;
		// |x|H| | | |T|x|x|
		}
		else
		{
			return 0;
		}
	// |T|x|x|x|H| | | |
	}else // == 0
	{
		// |T|x|x|x|x|x|x|H|
		if(CAN1TxBuffer.sFrameBufferHead == _CAN_TX_BUFFER_SIZE-1)
		{
			return 1;
		// |T|x|x|x|x|H| | |
		}else
		{
			return 0;
		}
	}
}
u8 CAN2_CheckOverflow(void)
{
	// | | |T|x|x|x|H| |
	if(CAN2TxBuffer.sFrameBufferTail != 0)
	{
		// |x|H|T|x|x|x|x|x|
		if(CAN2TxBuffer.sFrameBufferHead == CAN2TxBuffer.sFrameBufferTail-1)
		{
			return 1;
		// |x|H| | | |T|x|x|
		}
		else
		{
			return 0;
		}
	// |T|x|x|x|H| | | |
	}else // == 0
	{
		// |T|x|x|x|x|x|x|H|
		if(CAN2TxBuffer.sFrameBufferHead == _CAN_TX_BUFFER_SIZE-1)
		{
			return 1;
		// |T|x|x|x|x|H| | |
		}else
		{
			return 0;
		}
	}
}
void CAN_TurnOnPowerSaveMode(void)
{
	GPIO_SetBits(_CAN_NEN_GPIO,_CAN_NEN_PIN);
}
void CAN_TurnOffPowerSaveMode(void)
{
	GPIO_ResetBits(_CAN_NEN_GPIO,_CAN_NEN_PIN);
}


