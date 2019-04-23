#include "main.h"
#include "can.h"
#include "CAN2_functions.h"
#include "CAN2flags.h"
#include "stm32f4xx.h"
#include "flags.h"
#include "initSystemFunctions.h"
#include "functions.h"

//can variables
extern CanRxMsg CAN2_rFrame;
extern typ_CANTxBuffer CAN2TxBuffer;

//data structures
extern typ_ODSsesnorData ID_list[MAX_NUMBER_OF_SENSOR_BOARDS];
extern typ_ODSmainData ODSmainData;
extern typ_ODSlidarData ODSlidarData;

void CAN_DecodeFrame(CanRxMsg *RxMessage) {
	switch ((RxMessage->StdId)) {
	case _CAN_INIT_SERIAL:
		CAN_DecodeInitialFrames(RxMessage);
		break;
	case _CAN_INIT_TIME:
		CAN_Decode_MessureTime(RxMessage);
		break;
	case _CAN_DATA_DISTANCE:
		CAN_Decode_DistanceFrame(RxMessage);
		break;
	case _CAN_DATA_ERROR:
		CAN_Decode_ErrorFrame(RxMessage);
		break;
	case _CAN_DATA_LUX:
		CAN_Decode_LuxFrame(RxMessage);
		break;
	case _CAN_DATA_TEMP:
		CAN_Decode_TemperatureFrame(RxMessage);
		break;
	case _CAN_DATA_LIDAR:
		CAN_DecodeLidarData(RxMessage);
	case _CAN_INIT_LIDAR:
		CAN_DecodeInitLidar();
		break;
	default:
		break;
	}
}

void CAN_Decode_LuxFrame(CanRxMsg *RxMessage)
{
	uint32_t ID=*((uint32_t*)(&RxMessage->Data[0]));
	ID_list[ID].luxValue = *((float*)(&RxMessage->Data[4]));
	SetBits(ID_list[ID].recivedFlag,_REC_FLAG_LUX);
}
void CAN_Decode_TemperatureFrame(CanRxMsg *RxMessage)
{
	uint32_t ID=*((uint32_t*)(&RxMessage->Data[0]));
	ID_list[ID].temperatureValue = *((float*)(&RxMessage->Data[4]));
	SetBits(ID_list[ID].recivedFlag,_REC_FLAG_TEMP);
}
void CAN_Decode_DistanceFrame(CanRxMsg *RxMessage)
{
	uint32_t ID=*((uint32_t*)(&RxMessage->Data[0]));
	ID_list[ID].distanceValue = *((uint32_t*)(&RxMessage->Data[4]));
	SetBits(ID_list[ID].recivedFlag,_REC_FLAG_DIST);
}
void CAN_Decode_ErrorFrame(CanRxMsg *RxMessage)
{
	uint32_t ID=*((uint32_t*)(&RxMessage->Data[0]));
	ID_list[ID].errorFlag = *((uint32_t*)(&RxMessage->Data[4]));

	//if odssesnor board error flag is different than 0, set bit in ODSmain error variable
	if(ID_list[ID].errorFlag)
	{
		SetBits(ODSmainData.errorFlagPart2,(_ODSSESNOR_0_ERR+ID));
	}
	else
	{
		ResetBits(ODSmainData.errorFlagPart2,(_ODSSESNOR_0_ERR+ID));
	}
	SetBits(ID_list[ID].recivedFlag,_REC_FLAG_ERR);
}

void CAN_DecodeInitialFrames(CanRxMsg* RxMessage)
{
	//searching if serialID is in database
	uint8_t isSerialIDInDatabase=0;
	uint32_t serialID1=U8_Array_to_U32(&RxMessage->Data[0]);
	uint32_t serialID2=U8_Array_to_U32(&RxMessage->Data[4]);
	for(uint8_t i=0;i<ODSmainData.numberOfODSsensrs;i++)
	{
		if((serialID1==ID_list[i].serial_ID1)&&(serialID2==ID_list[i].serial_ID2))
		{
			//if there is already serialID in database, send ODS_ID to ODSsensor without changing it

			CAN_SendODS_ID(&ID_list[i].serial_ID1,&ID_list[i].serial_ID2,ID_list[i].ODS_ID);
			isSerialIDInDatabase=1;
			break;
		}
	}

	if(!isSerialIDInDatabase) //if there isn't in database add it and send new ODS_ID to ODSsensor
	{
		AddNewElementToIDList(&serialID1,&serialID2);
		CAN_SendODS_ID(&serialID1,&serialID2,ID_list[ODSmainData.numberOfODSsensrs-1].ODS_ID);
	}
}
void CAN_SendODS_ID(uint32_t *serialID_1,uint32_t *serialID_2, uint8_t ODS_ID)
{
	uint32_t ID=(uint32_t) ODS_ID;
	uint32_t emptySlot=0;
	CAN2_SendFrameWithBuffer(_CAN_INIT_ADDRESS,serialID_1,serialID_2);
	CAN2_SendFrameWithBuffer(_CAN_INIT_ADDRESS2,&ID,&emptySlot);
}

void MessureTime_SendFrame()
{
	if(ODSmainData.MeassureTime_CurrentID<ODSmainData.numberOfODSsensrs)
	{
		TIM7->CNT=0;
		CAN2_SendFrameWithBuffer(_CAN_INIT_TIME,&ID_list[ODSmainData.MeassureTime_CurrentID].serial_ID1,&ID_list[ODSmainData.MeassureTime_CurrentID].serial_ID2);
		TIM_Cmd(TIM7, ENABLE);
	}
	else{
		ODSmainData.MeassureTime_IsGoing=0;
		ODSmainData.MeassureTime_CurrentID=0;
		TIM_Cmd(TIM7, DISABLE);
		TIM7->CNT=0;
		SortList(ID_list,ODSmainData.numberOfODSsensrs); //sorting id list
		DeleteNoTimeIDsFromSortedList(ID_list);
		for(uint8_t i=0;i<ODSmainData.numberOfODSsensrs;i++) //give new id
		{
			ID_list[i].ODS_ID=i;
			CAN_SendODS_ID(&ID_list[i].serial_ID1,&ID_list[i].serial_ID2,ID_list[i].ODS_ID);
		}
		SaveListOfIDs();                           //save id list in flash
	}
}

void CAN_Decode_MessureTime(CanRxMsg* RxMessage)
{
	TIM_Cmd(TIM7,DISABLE);
	uint32_t serialID1=U8_Array_to_U32(&RxMessage->Data[0]);
	uint32_t serialID2=U8_Array_to_U32(&RxMessage->Data[4]);
	if((ID_list[ODSmainData.MeassureTime_CurrentID].serial_ID1==serialID1)&&(ID_list[ODSmainData.MeassureTime_CurrentID].serial_ID2 == serialID2))
	{
		ID_list[ODSmainData.MeassureTime_CurrentID].meassuredTime=TIM7->CNT;
		TIM7->CNT=0;
		ODSmainData.MeassureTime_CurrentID++;
		MessureTime_SendFrame();
	}
}


void CAN_DecodeInitLidar()
{
	uint32_t emptySlot=0;
	CAN2_SendFrameWithBuffer(_CAN_INIT_LIDAR,&emptySlot,&emptySlot);
}
void CAN_DecodeLidarData(CanRxMsg* RxMessage)
{
	ODSlidarData.distanceValue=U8_Array_to_U32(&RxMessage->Data[0]);
	ODSlidarData.errorFlag=U8_Array_to_U32(&RxMessage->Data[4]);
	if(ODSlidarData.errorFlag!=0)
	{
		SetBits(ODSmainData.errorFlagPart2,_ODSLIDAR_ERR);
	}
}
