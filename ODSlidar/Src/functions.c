/*
 * functions.c
 *
 *  Created on: 22.12.2018
 *      Author: Patryk
 */

#include "stm32l4xx_hal.h"
#include "functions.h"

void Clear_typLidarBoard(typ_LidarBoard *structure)
{
	structure->errorFlag=0;
	structure->distanceValue=0;
	structure->counter=0;
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
void HAL_Delay(uint32_t milliseconds)
{
   /* Initially clear flag */
   (void) SysTick->CTRL;

   while (milliseconds != 0) {
      /* COUNTFLAG returns 1 if timer counted to 0 since the last flag read */
      milliseconds -= (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) >> SysTick_CTRL_COUNTFLAG_Pos;
   }
}
