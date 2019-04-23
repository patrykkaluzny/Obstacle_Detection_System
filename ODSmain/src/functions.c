/*
 * functions.c
 *
 *  Created on: 07.12.2018
 *      Author: Patryk
 */
#include "functions.h"

uint32_t U8_Array_to_U32(uint8_t *array)
{
	uint32_t *value=(uint32_t*)array;
	return *value;
}
void Double_U32_to_U8_Array(uint8_t *array, uint32_t *variable_1,uint32_t *variable_2)
{
	for(uint8_t i=0;i<4;i++)
	{
		array[i]=*variable_1>>(i*8);
	}
	for(uint8_t i=4;i<8;i++)
	{
		array[i]=*variable_2>>((i-4)*8);
	}
}

void Clear_typ_ODSmainData(typ_ODSmainData *structure)
{
	structure->errorFlagPart1=0;
	structure->errorFlagPart2=0;
	structure->numberOfODSsensrs=0;
	structure->MeassureTime_CurrentID=0;
	structure->MeassureTime_IsGoing=0;
}
void Clear_typODSsenosrData(typ_ODSsesnorData *StructToClear)
{
	StructToClear->ODS_ID=0;
	StructToClear->meassuredTime=0;
	StructToClear->serial_ID1=0;
	StructToClear->serial_ID2=0;
	StructToClear->distanceValue=0;
	StructToClear->luxValue=0;
	StructToClear->temperatureValue=0;
	StructToClear->errorFlag=0;
	StructToClear->recivedFlag=0;

}

