/*
 * functions.h
 *
 *  Created on: 22.12.2018
 *      Author: Patryk
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "structures.h"

void Clear_typLidarBoard(typ_LidarBoard *structure);
void Double_U32_to_U8_Array(uint8_t *array, uint32_t *variable_1,uint32_t *variable_2);
void HAL_Delay(uint32_t milliseconds);
#endif /* FUNCTIONS_H_ */
