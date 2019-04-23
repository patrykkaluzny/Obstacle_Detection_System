/*
 * structures.h
 *
 *  Created on: 05.12.2018
 *      Author: Patryk
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_


// CAN buffer structure
typedef struct typ_CANTxBuffer
{
	CanTxMsg sFrameBuffer[_CAN_TX_BUFFER_SIZE];
	uint8_t sFrameBufferTail;
	uint8_t sFrameBufferHead;
	uint8_t sFrameBufferOVF;
}typ_CANTxBuffer;


typedef struct typ_ODSmainData
{
	uint32_t numberOfODSsensrs;
	uint8_t MeassureTime_CurrentID;
	uint8_t MeassureTime_IsGoing;
	uint32_t errorFlagPart1; //todo fill with errors from ODSmain
	uint32_t errorFlagPart2;
}typ_ODSmainData;

typedef struct typ_ODSlidarData
{
	uint32_t distanceValue;
	uint32_t errorFlag;
}typ_ODSlidarData;

typedef struct typ_ODSsesnorData
{
	//id data
	uint32_t serial_ID1;  // unique serial number of microcontroller from ODSsensor, part1
	uint32_t serial_ID2;  // unique serial number of microcontroller from ODSsensor, part2
	uint8_t ODS_ID;      // ID grunted by ODSmain

	//sorting data
	uint32_t meassuredTime; // time of CAN message

	//data from sensors
	float temperatureValue;
	float luxValue;
	uint32_t distanceValue;

	//flags
	uint32_t errorFlag;
	uint8_t recivedFlag;


	/* bits of errorFlag
		 * 0 - ID - 		0 - board has ID						1 - there is no ID sent from ODSmain  //if it's board starts sending data to ODSmain
		 * 1 - luxRead - 	0 - lux read is working properly, 		1 - error during lux reading
		 * 2 - tempRead - 	0 - temp read is working properly, 		1 - error during temp reading
		 * 3 - initVL53L0 - 0 - init done properly,					1 - error during init
		 * 4
		 * 5
		 * 6
		 * 7
		 * 8
		 * 9
		 * 10
		 *  // up to 31
		 *
		 *
		 */
	/* bits of reciveFlag
			 * 0 - distanceRecive - 	0 - distance not received		1 - distance received
			 * 1 - luxRecive - 			0 - lux not received 			1 - lux received
			 * 2 - tempRecive - 		0 - temp not received 			1 - temp received
			 * 3 - errorRecive - 		0 - errorFlag not received		1 - errorFlag received
			 * 4
			 * 5
			 * 6
			 * 7
			 */



}typ_ODSsesnorData;


#endif /* STRUCTURES_H_ */
