/*
 * CAN2_functions.h
 *
 *  Created on: 30.12.2018
 *      Author: Patryk
 */

#ifndef CAN2_FUNCTIONS_H_
#define CAN2_FUNCTIONS_H_

#include "structures.h"

void CAN_DecodeFrame(CanRxMsg *RxMessage);
void CAN_Decode_LuxFrame(CanRxMsg *RxMessage);
void CAN_Decode_TemperatureFrame(CanRxMsg *RxMessage);
void CAN_Decode_DistanceFrame(CanRxMsg *RxMessage);
void CAN_Decode_ErrorFrame(CanRxMsg *RxMessage);
void CAN_DecodeInitialFrames(CanRxMsg* RxMessage);
void CAN_SendODS_ID(uint32_t *serialID_1,uint32_t *serialID_2, uint8_t ODS_ID);
void MessureTime_SendFrame();
void CAN_Decode_MessureTime(CanRxMsg* RxMessage);
void CAN_DecodeInitLidar();
void CAN_DecodeLidarData(CanRxMsg* RxMessage);

#endif /* CAN2_FUNCTIONS_H_ */
