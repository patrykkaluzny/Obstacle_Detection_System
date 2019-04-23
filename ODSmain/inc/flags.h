/*
 * errorFlags.h
 *
 *  Created on: 17.12.2018
 *      Author: Patryk
 */

#ifndef FLAGS_H_
#define FLAGS_H_
//////////error flags///////////////////////////////////
//ODSsensor flags
#define ODSSENSOR_ERROR_ID				0
#define ODSSENSOR_ERROR_LUX 			1
#define ODSSENSOR_ERROR_TEMP			2
#define ODSSENSOR_ERROR_INIT_VL53L0		3

//reciveFlag errors
#define _REC_FLAG_DIST 			0 //0 - distance not received		1 - distance received
#define _REC_FLAG_LUX			1 //0 - lux not received 			1 - lux received
#define _REC_FLAG_TEMP 			2 //0 - temp not received 			1 - temp received
#define _REC_FLAG_ERR			3 //0 - errorFlag not received		1 - errorFlag received

//ODSmain errorFlagPart1
#define _CAN1_BUFFER_OVF			0		// set if can1 buffer is overflowed
#define _CAN2_BUFFER_OVF			1		// set if can2 buffer is overflowed
#define _FLASH_CLEAR_ERR			2		// set if occurs error during flash data cleaning
#define _FLASH_SAVE_DIFF			3		// set if saved value is different than it should be
#define _FLASH_SAVE_ERR				4		// set if occurs error during saving data in flash memory
#define _MAX_BOARDS_REACHED 		5		// set if number of ODSsensors reached limit
#define _BOARD_WITHOUT_RESPONSE 	6       // set if there is board with measured time equals 0

//ODSmain errorFlagPart2


#define _ODSLIDAR_ERR			15	//indicates if odslidar has errors

#define _ODSSESNOR_0_ERR		16  //indicates if odssesnor1 has errors
#define _ODSSESNOR_1_ERR		17
#define _ODSSESNOR_2_ERR		18
#define _ODSSESNOR_3_ERR		19
#define _ODSSESNOR_4_ERR		20
#define _ODSSESNOR_5_ERR		21
#define _ODSSESNOR_6_ERR		22
#define _ODSSESNOR_7_ERR		23
#define _ODSSESNOR_8_ERR		24
#define _ODSSESNOR_9_ERR		25
#define _ODSSESNOR_10_ERR		26
#define _ODSSESNOR_11_ERR		27
#define _ODSSESNOR_12_ERR		28
#define _ODSSESNOR_13_ERR		29
#define _ODSSESNOR_14_ERR		30
#define _ODSSESNOR_15_ERR		31


////////CAN data flags ///////////////////////////////////

#endif /* FLAGS_H_ */
