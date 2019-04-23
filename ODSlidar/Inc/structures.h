/*
 * structures.h
 *
 *  Created on: 22.12.2018
 *      Author: Patryk
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include "stm32l4xx_hal.h"
#include "main.h"


typedef struct typ_LidarBoard
{
	//sensors data
	uint32_t distanceValue;

	//error flags
	uint32_t errorFlag; //todo fill with boards errors

	//measurement counter
	uint8_t counter;
}typ_LidarBoard;

typedef struct typ_CANTxBuffer									// CAN buffer structure
{
	CAN_TxHeaderTypeDef sFrameBuffer[_CAN_TX_BUFFER_SIZE];
	uint32_t sCANData1[_CAN_TX_BUFFER_SIZE];
	uint32_t sCANData2[_CAN_TX_BUFFER_SIZE];
	uint8_t sFrameBufferTail;
	uint8_t sFrameBufferHead;
	uint8_t sFrameBufferOVF;
}typ_CANTxBuffer;


#endif /* STRUCTURES_H_ */
