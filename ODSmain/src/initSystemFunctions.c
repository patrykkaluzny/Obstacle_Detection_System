/*
 * initSystemFunctions.c
 *
 *  Created on: 03.12.2018
 *      Author: Patryk
 */

#include "main.h"
#include "initSystemFunctions.h"
#include "CAN2flags.h"
#include "can.h"
#include "CAN2_functions.h"
#include "functions.h"
#include "flags.h"



extern typ_ODSsesnorData ID_list[MAX_NUMBER_OF_SENSOR_BOARDS];
extern volatile typ_ODSmainData ODSmainData;



int test=0;
void FLASH_Configuration()
{
	FLASH_SetLatency(FLASH_Latency_5); // based of system_stm32f4xx.c file, line 273
}
uint8_t SaveListOfIDs() // it works
{
	uint8_t FLASH_status;
	uint32_t* FLASH_Address=(uint32_t*)FLASH_START_ADRESS;

	//clear flash memory
	FLASH_status = FLASH_ClearIDData();
	if (FLASH_status != FLASH_COMPLETE) {
		SetBits(ODSmainData.errorFlagPart1,_FLASH_CLEAR_ERR);
		return FLASH_status;
	}
	//write list to flash

	FLASH_status=FLASH_WriteListOfID(FLASH_Address,ID_list,ODSmainData.numberOfODSsensrs);
	return FLASH_status;
}

uint8_t FLASH_WriteListOfID(uint32_t* FlashAddress, typ_ODSsesnorData *dataToWrite, uint8_t dataLength)
{
	//write number of sensor boards
	FLASH_Unlock();
	if (FLASH_ProgramWord((uint32_t)FlashAddress, (uint32_t)dataLength)== FLASH_COMPLETE) {
		//check the written value
		if (*FlashAddress != dataLength) {
			FLASH_Lock();
			SetBits(ODSmainData.errorFlagPart1,_FLASH_SAVE_DIFF);
			return 2; // Flash content doesn't match SRAM content
		}
		//increment flash address
		FlashAddress += sizeof(uint32_t);
	} else {
		/* Error occurred while writing data in Flash memory */
		SetBits(ODSmainData.errorFlagPart1,_FLASH_SAVE_ERR);
		FLASH_Lock();
		return (1);
	}
	FLASH_Lock();
	//write table to flash memory
	for(uint8_t i=0;i<=dataLength;i++)
	{
		FLASH_Unlock();

		//save part1
		if (FLASH_ProgramWord((uint32_t)FlashAddress, dataToWrite[i].serial_ID1) == FLASH_COMPLETE)
		{
			//check the written value
			if(*FlashAddress != dataToWrite[i].serial_ID1){
				FLASH_Lock();
				SetBits(ODSmainData.errorFlagPart1,_FLASH_SAVE_DIFF);
				return 2; // Flash content doesn't match SRAM content
			}
			//increment flash address
			FlashAddress += sizeof(uint32_t);
		}
		else
		{
			/* Error occurred while writing data in Flash memory */
			SetBits(ODSmainData.errorFlagPart1,_FLASH_SAVE_ERR);
			FLASH_Lock();
			return (1);
		}

		//save part 2
		if (FLASH_ProgramWord((uint32_t) FlashAddress,dataToWrite[i].serial_ID2) == FLASH_COMPLETE) {
			//check the written value

			if (*FlashAddress!= dataToWrite[i].serial_ID2) {
				FLASH_Lock();
				SetBits(ODSmainData.errorFlagPart1,_FLASH_SAVE_DIFF);
				return 2; // Flash content doesn't match SRAM content
			}
			//increment flash address
			FlashAddress += sizeof(uint32_t);
		} else {
			/* Error occurred while writing data in Flash memory */
			SetBits(ODSmainData.errorFlagPart1,_FLASH_SAVE_ERR);
			FLASH_Lock();
			return (1);
		}
		FLASH_Lock();
	}
	return 0;
}
uint8_t FLASH_ReadListOFIDs()
{
	ClearListOfIDs();
	uint32_t* FLASH_Address = (uint32_t *) FLASH_START_ADRESS;
	if (*FLASH_Address == 0xFFFFFFFF) // flash is empty, all bits are 1
			{
		return 1; // flash was cleared, nothing to read;
	} else {
		//read number of sensor boards from flash
		ODSmainData.numberOfODSsensrs = *FLASH_Address;
		FLASH_Address += sizeof(uint32_t);

		//read array of IDs from flash

		for (uint8_t i = 0; i < ODSmainData.numberOfODSsensrs; i++)
		{
			ID_list[i].serial_ID1 = *FLASH_Address;
			FLASH_Address += sizeof(uint32_t);
			ID_list[i].serial_ID2 = *FLASH_Address;
			FLASH_Address += sizeof(uint32_t);
			ID_list[i].ODS_ID = i;
		}
		return 0; //id data read from flash
	}
}
uint8_t AddNewElementToIDList(uint32_t* newSnsorID1,uint32_t* newSnsorID2)
{
	if(ODSmainData.numberOfODSsensrs<MAX_NUMBER_OF_SENSOR_BOARDS)
	{

		ID_list[ODSmainData.numberOfODSsensrs].serial_ID1=*newSnsorID1;
		ID_list[ODSmainData.numberOfODSsensrs].serial_ID2=*newSnsorID2;

		ID_list[ODSmainData.numberOfODSsensrs].ODS_ID=ODSmainData.numberOfODSsensrs;
		ODSmainData.numberOfODSsensrs++;
		uint8_t FLASH_Status= SaveListOfIDs();
		return FLASH_Status;
	}
	else {
		//max limit of boards has been reached
		SetBits(ODSmainData.errorFlagPart1,_MAX_BOARDS_REACHED);
		return 0xF;
	}
}
uint8_t FLASH_ClearIDData()
{
	uint8_t FLASH_status;
	FLASH_Unlock();
	FLASH_status = FLASH_EraseSector(FLASH_SECTOR,VoltageRange_3);
	FLASH_Lock();
	return FLASH_status;
}

void StartTimeMeassuringProcedure()
{
	ODSmainData.MeassureTime_CurrentID=0;
	ODSmainData.MeassureTime_IsGoing=1;

	MessureTime_SendFrame();
}
void SortList(typ_ODSsesnorData *ListToSort, uint8_t NumberOfElements)
{
	for (uint8_t i = 0; i <NumberOfElements - 1; ++i) {
		for (uint8_t j = 0; j <NumberOfElements-i-1 ; ++j) {
			if (ListToSort[j].meassuredTime > ListToSort[j+1].meassuredTime) {
				typ_ODSsesnorData temp = ListToSort[j];
				ListToSort[j] = ListToSort[j+1];
				ListToSort[j+1] = temp;
			}
		}
	}
}
void DeleteNoTimeIDsFromSortedList(typ_ODSsesnorData *SortedList)
{
	uint8_t NumberOfIDToDelete=0;
	for(uint8_t i=0;i<ODSmainData.numberOfODSsensrs;i++)
	{
		if(SortedList[i].meassuredTime==0)
		{
			SetBits(ODSmainData.errorFlagPart1,_BOARD_WITHOUT_RESPONSE);
			NumberOfIDToDelete++;
		}
		else{break;}
	}
	if (NumberOfIDToDelete > 0) {

		for (uint8_t i = NumberOfIDToDelete; i < ODSmainData.numberOfODSsensrs; i++) {
			SortedList[i - NumberOfIDToDelete] = SortedList[i];
		}
		for(uint8_t i=ODSmainData.numberOfODSsensrs-NumberOfIDToDelete;i<ODSmainData.numberOfODSsensrs;i++)
		{
			Clear_typODSsenosrData(&ID_list[i]);
		}
		ODSmainData.numberOfODSsensrs -= NumberOfIDToDelete;
	}
}
void ClearListOfIDs()
{
	for(uint8_t i=0;i<MAX_NUMBER_OF_SENSOR_BOARDS;i++)
	{
		Clear_typODSsenosrData(&ID_list[i]);
	}
	ODSmainData.numberOfODSsensrs=0;
}




