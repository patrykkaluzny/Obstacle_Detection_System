/*
 * general_functions.h
 *
 *  Created on: 07.12.2018
 *      Author: Patryk
 */

#ifndef GENERAL_FUNCTIONS_H_
#define GENERAL_FUNCTIONS_H_

#include "stm32l4xx_hal.h"
#include "structures.h"

uint32_t U8_Array_to_U32(uint8_t *array);
void Double_U32_to_U8_Array(uint8_t *array, uint32_t *variable_1,uint32_t *variable_2);
void ClearDataToSend(typ_DataToSend *structure);
void HAL_Delay(uint32_t milliseconds);
#endif /* GENERAL_FUNCTIONS_H_ */
