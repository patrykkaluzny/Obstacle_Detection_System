/************************* Description ******************************
* File Name			: CANflags.h
* Author			: PART
* Version			: V0.0.0
* Date				: 2018-12-23 11:06:18
* Description		: Identyfikatory paczek wystêpuj¹cych w pok³adowej magistrali CAN
********************************************************************/

////// _CAN_ODS_INIT //////
#define 	_CAN_INIT_TIME		0x003		// Time measuring pack
#define 	_CAN_INIT_SERIAL	0x005		// Unique serial ID sent by ODSsendor
#define 	_CAN_INIT_ADDRESS	0x006		// Unique serial ID sent by ODSmain to prepare ODSsensor to recive ODS ID
#define 	_CAN_INIT_ADDRESS2	0x007		// ODS ID granted by ODSmain to ODSsensor
#define 	_CAN_INIT_LIDAR		0x009		// Initialization frame for ODSlidar

////// _CAN_ODS_MAIN //////

////// _CAN_ODS_DATA //////
#define 	_CAN_DATA_ERROR		0x085		// ODS_ID of ODSsensor and errors of the board
#define 	_CAN_DATA_DISTANCE	0x086		// ODS_ID of ODSsensor and measured distance
#define 	_CAN_DATA_LUX		0x087		// ODS_ID of ODSsensor and measured lux
#define 	_CAN_DATA_TEMP		0x088		// ODS_ID of ODSsensor and measured temparture
#define 	_CAN_DATA_LIDAR		0x08A		// Data and errors from ODSlidar

////// _CAN_ODS_SENSOR0 //////

////// _CAN_ODS_SENSOR1 //////

////// _CAN_ODS_SENSOR2 //////

////// _CAN_ODS_SENSOR3 //////

////// _CAN_ODS_SENSOR4 //////

////// _CAN_ODS_SENSOR5 //////

////// _CAN_ODS_SENSOR6 //////

////// _CAN_ODS_SENSOR7 //////

////// _CAN_ODS_SENSOR8 //////

////// _CAN_ODS_SENSOR9 //////

////// _CAN_ODS_SENSOR10 //////

////// _CAN_ODS_SENSOR11 //////

////// _CAN_ODS_SENSOR12 //////

