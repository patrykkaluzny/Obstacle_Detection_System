/*
 * general_functions.c
 *
 *  Created on: 07.12.2018
 *      Author: Patryk
 */

#include "general_functions.h"

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
void ClearDataToSend(typ_DataToSend *structure)
{
	structure->ID=0;
	structure->distanceValue=0;
	structure->luxValue=0;
	structure->temperatureValue=0;
	structure->errorFlag=0;
}

void HAL_Delay(uint32_t milliseconds)
{
   /* Initially clear flag */
   (void) SysTick->CTRL;

   while (milliseconds != 0) {
      /* COUNTFLAG returns 1 if timer counted to 0 since the last flag read */
      milliseconds -= (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) >> SysTick_CTRL_COUNTFLAG_Pos;
   }
}
