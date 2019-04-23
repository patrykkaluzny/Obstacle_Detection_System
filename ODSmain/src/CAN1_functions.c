#include "main.h"
#include "can.h"
#include "CAN1_functions.h"
#include "CAN1flags.h"
#include "stm32f4xx.h"

extern CanRxMsg CAN1_rFrame;

extern typ_CANTxBuffer CAN1TxBuffer;

extern typ_ODSsesnorData ID_list[MAX_NUMBER_OF_SENSOR_BOARDS];
extern typ_ODSmainData ODSmainData;
extern typ_ODSlidarData ODSlidarData;


//decoding functions/////////////////////////
void CAN1_Decode(CanRxMsg *RxMessage)
{
	switch ((RxMessage->StdId)) {
		case _CAN_GET_ODSSENS_ERR:
			CAN1_Decode_GetErr();
			break;
		case _CAN_GET_ODSSENS_LUX:
			CAN1_Decode_GetLux();
			break;
		case _CAN_GET_ODSSENS_TEMP:
			CAN1_Decode_GetTemp();
			break;
		case _CAN_NUM_ODS_SENS:
			CAN1_Decode_GetNum();
			break;
		case _CAN_ODS_ERR_MAIN:
			CAN1_Decode_ErrMain();
			break;
		}
}
void CAN1_Decode_GetNum()
{
	uint32_t EmptySlot=0x0;
	CAN1_SendFrameWithBuffer(_CAN_NUM_ODS_SENS,&ODSmainData.numberOfODSsensrs,&EmptySlot);
}

void CAN1_Decode_ErrMain()
{
	CAN1_SendFrameWithBuffer(_CAN_ODS_ERR_MAIN,&ODSmainData.errorFlagPart1,&ODSmainData.errorFlagPart2);
}
void CAN1_Decode_GetErr()
{
	//sending errors values from ODSsensor
	uint32_t flagValue = (uint32_t) _CAN_ODS_ERR_0_1;
	for (uint8_t i = 0; i < ODSmainData.numberOfODSsensrs; i += 2, flagValue++) {
		CAN1_SendFrameWithBuffer(flagValue, &ID_list[i].errorFlag,
				&ID_list[i + 1].errorFlag);
	}

}
void CAN1_Decode_GetTemp()
{
	//sending temp values from ODSsensor
		uint32_t flagValue = (uint32_t) _CAN_ODS_TEMP_0_1;
		uint32_t *address1;
		uint32_t *address2;
		for (uint8_t i = 0; i < ODSmainData.numberOfODSsensrs; i += 2, flagValue++) {
			address1=(uint32_t *)&ID_list[i].temperatureValue;
			address2=(uint32_t *)&ID_list[i+1].temperatureValue;
			CAN1_SendFrameWithBuffer(flagValue, address1,address2);
		}
}
void CAN1_Decode_GetLux()
{
	//sending lux values from ODSsensor
	uint32_t flagValue = (uint32_t) _CAN_ODS_LUX_0_1;
	uint32_t *address1;
	uint32_t *address2;
	for (uint8_t i = 0; i < ODSmainData.numberOfODSsensrs; i += 2, flagValue++) {
		address1=(uint32_t *)&ID_list[i].luxValue;
		address2=(uint32_t *)&ID_list[i+1].luxValue;
		CAN1_SendFrameWithBuffer(flagValue, address1,address2);
	}

}

////////sending functions//////////////////////

void CAN1_SendDistance()
{
	//sending distance values from ODSsensor
	uint32_t flagValue = (uint32_t)_CAN_NUM_ODS_SENS;
	uint32_t emptySlot=0x0;
	CAN1_SendFrameWithBuffer(flagValue,&ODSmainData.numberOfODSsensrs,&emptySlot);

	flagValue = (uint32_t)_CAN_ODS_DIST_0_1;
	for(uint8_t i=0;i<ODSmainData.numberOfODSsensrs;i+=2,flagValue++)
	{
		CAN1_SendFrameWithBuffer(flagValue,&ID_list[i].distanceValue,&ID_list[i+1].distanceValue);
	}



}
void CAN1_SendLidar()
{
	uint32_t flagValue = (uint32_t)_CAN_ODS_LIDAR;
	CAN1_SendFrameWithBuffer(flagValue,&ODSlidarData.distanceValue,&ODSlidarData.errorFlag);
}

