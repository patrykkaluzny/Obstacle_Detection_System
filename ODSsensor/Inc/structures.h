/*
 * structures.h
 *
 *  Created on: 15.12.2018
 *      Author: Patryk
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include "vl53l0x_types.h"

typedef struct typ_VL53L0_InitData                             //init data structure for vl53l0 sensor
{
	uint8_t isManufacturingInitDone;
	uint32_t  refSpadCount;
	uint8_t  isApertureSpads ;
	uint8_t  vhvSettings;
	uint8_t  phaseCal;
	int32_t  offsetMicroMeter;
	FixPoint1616_t xTalkCompensationRateMegaCps;
	float initTemp;
}typ_VL53L0_InitData;

typedef struct typ_CANTxBuffer									// CAN buffer structure
{
	CAN_TxHeaderTypeDef sFrameBuffer[_CAN_TX_BUFFER_SIZE];
	uint32_t sCANData1[_CAN_TX_BUFFER_SIZE];
	uint32_t sCANData2[_CAN_TX_BUFFER_SIZE];
	uint8_t sFrameBufferTail;
	uint8_t sFrameBufferHead;
	uint8_t sFrameBufferOVF;
}typ_CANTxBuffer;

typedef struct typ_DataToSend
{
	//sensors data
	float temperatureValue;
	float luxValue;
	uint32_t distanceValue;

	//board ID
	uint32_t ID;

	//error flags
	uint32_t errorFlag; //todo fill with boards errors

	uint8_t isInitDone;
}typ_DataToSend;

#endif /* STRUCTURES_H_ */
