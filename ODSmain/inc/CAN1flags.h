/************************* Description ******************************
* File Name			: CANflags.h
* Author			: PART
* Version			: V0.0.0
* Date				: 2019-01-10 17:33:23
* Description		: Identyfikatory paczek wystêpuj¹cych w pok³adowej magistrali CAN
********************************************************************/

////// _CAN_ODS //////
#define 	_CAN_ODS_ERR_MAIN	0x280		// ODSmain errors
#define 	_CAN_GET_ODSSENS_ERR	0x282		// Get errors from ODSsesnors
#define 	_CAN_GET_ODSSENS_TEMP	0x283		// Get temp data from ODSsesnors
#define 	_CAN_GET_ODSSENS_LUX	0x284		// Get lux data from ODSsesnors
#define 	_CAN_NUM_ODS_SENS	0x286		// Get number of sensor boards
#define 	_CAN_ODS_DIST_0_1	0x288		// Measured distance
#define 	_CAN_ODS_DIST_2_3	0x289		// Measured distance
#define 	_CAN_ODS_DIST_4_5	0x28A		// Measured distance
#define 	_CAN_ODS_DIST_6_7	0x28B		// Measured distance
#define 	_CAN_ODS_DIST_8_9	0x28C		// Measured distance
#define 	_CAN_ODS_DIST_10_11	0x28D		// Measured distance
#define 	_CAN_ODS_DIST_12_13	0x28E		// Measured distance
#define 	_CAN_ODS_DIST_14_15	0x28F		// Measured distance
#define 	_CAN_ODS_LIDAR		0x292		// Measured distance by Lidar sensor and errors from ODSlidar
#define 	_CAN_ODS_ERR_0_1	0x295		// ODSsensor errors
#define 	_CAN_ODS_ERR_2_3	0x296		// ODSsensor errors
#define 	_CAN_ODS_ERR_4_5	0x297		// ODSsensor errors
#define 	_CAN_ODS_ERR_6_7	0x298		// ODSsensor errors
#define 	_CAN_ODS_ERR_8_9	0x299		// ODSsensor errors
#define 	_CAN_ODS_ERR_10_11	0x29A		// ODSsensor errors
#define 	_CAN_ODS_ERR_12_13	0x29B		// ODSsensor errors
#define 	_CAN_ODS_ERR_14_15	0x29C		// ODSsensor errors
#define 	_CAN_ODS_TEMP_0_1	0x2A0		// Measured temperature
#define 	_CAN_ODS_TEMP_2_3	0x2A1		// Measured temperature
#define 	_CAN_ODS_TEMP_4_5	0x2A2		// Measured temperature
#define 	_CAN_ODS_TEMP_6_7	0x2A3		// Measured temperature
#define 	_CAN_ODS_TEMP_8_9	0x2A4		// Measured temperature
#define 	_CAN_ODS_TEMP_10_11	0x2A5		// Measured temperature
#define 	_CAN_ODS_TEMP_12_13	0x2A6		// Measured temperature
#define 	_CAN_ODS_TEMP_14_15	0x2A7		// Measured temperature
#define 	_CAN_ODS_LUX_0_1	0x2AD		// Measured lux
#define 	_CAN_ODS_LUX_2_3	0x2AE		// Measured lux
#define 	_CAN_ODS_LUX_4_5	0x2AF		// Measured lux
#define 	_CAN_ODS_LUX_6_7	0x2B0		// Measured lux
#define 	_CAN_ODS_LUX_8_9	0x2B1		// Measured lux
#define 	_CAN_ODS_LUX_10_11	0x2B2		// Measured lux
#define 	_CAN_ODS_LUX_12_13	0x2B3		// Measured lux
#define 	_CAN_ODS_LUX_14_15	0x2B4		// Measured lux
#define 	_CAN_ODS_STATUS		0x2BF		// ODS module register
