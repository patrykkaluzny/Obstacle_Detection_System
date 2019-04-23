/*
 * functions.h
 *
 *  Created on: 07.12.2018
 *      Author: Patryk
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "main.h"
#include "structures.h"

uint32_t U8_Array_to_U32(uint8_t *array);
void Double_U32_to_U8_Array(uint8_t *array, uint32_t *variable_1,uint32_t *variable_2);
void Clear_typ_ODSmainData(typ_ODSmainData *structure);
void Clear_typODSsenosrData(typ_ODSsesnorData *StructToClear);


#endif /* FUNCTIONS_H_ */
