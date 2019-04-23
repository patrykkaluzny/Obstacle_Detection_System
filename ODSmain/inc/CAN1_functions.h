/*
 * CAN1_functions.h
 *
 *  Created on: 21.12.2018
 *      Author: Patryk
 */

#ifndef CAN1_FUNCTIONS_H_
#define CAN1_FUNCTIONS_H_

#include "structures.h"

void CAN1_Decode(CanRxMsg *RxMessage);
void CAN1_Decode_GetNum();
void CAN1_Decode_ErrMain();
void CAN1_Decode_GetErr();
void CAN1_Decode_GetTemp();
void CAN1_Decode_GetLux();
void CAN1_SendDistance();
void CAN1_SendLidar();
#endif /* CAN1_FUNCTIONS_H_ */
