/*
 * errorFlags.h
 *
 *  Created on: 17.12.2018
 *      Author: Patryk
 */

#ifndef ERRORFLAGS_H_
#define ERRORFLAGS_H_

// odssensor errors
#define ODSSENSOR_ERROR_ID				  				0 //0 - board has ID						1 - there is no ID sent from ODSmain  //if it's board starts sending data to ODSmain
#define ODSSENSOR_ERROR_LUX 			  				1 //0 - lux read is working properly, 		1 - error during lux reading
#define ODSSENSOR_ERROR_TEMP			  				2 //0 - temp read is working properly, 		1 - error during temp reading
#define ODSSENSOR_ERROR_INIT_VL53L0		  				3 //0 - init done properly,					1 - error during init
#define ODSSENSOR_ERROR_DATAINIT    	  				4 //0 - dataInit done properly,				1 - error during dataInit
#define ODSSENSOR_ERROR_STATICINIT        				5 //0 - staticInit done properly,			1 - error during staticInit
#define ODSSENSOR_ERROR_REF_SPAD_MANAGEMENT    		 	6 //0 - RefSpadManagement done properly,    1 - error during RefSpadManagement
#define ODSSENSOR_ERROR_REF_CALIBRATION					7 //0 - RefCalibration done properly,		1 - error during RefCalbration
#define ODSSENSOR_ERROR_OFFSET_CALIBRATION     			8 //0 - OffsetCalibration done properly,    1 - error during OffsetCalibration
#define ODSSENSOR_ERROR_XTALK_CALIBRATION       		9 //0 - XTalkCalibration done properly,     1 - error during XTalkCalibration
#define ODSSENSOR_ERROR_CALLBACK_GET_MEASUREMENT_DATA_READY  		10//0 - ok,  					1 - error during GetMeasurementDataReady
#define ODSSENSOR_ERROR_CALLBACK_GET_RANGING_MEASUREMENT_DATA       11//0 - ok,  					1 - error during GetRangingMeasurementData
#define ODSSENSOR_ERROR_CALLBACK_CLEAR_INTERRUPT_MASK        		12//0 - ok,  					1 - error during ClearInterruptMask
#define ODSSENSOR_ERROR_RANGING_SETUP_SET_DEVICE_MODE				13//0 - ok,						1 - error during SetDeviceMode
#define ODSSENSOR_ERROR_RANGING_INTER_MEASUREMENT_PERIOD			14//0 - ok,						1 - error during SetInterMeasurementPeriodMilliSeconds
#define ODSSENSOR_ERROR_RANGING_MEASUREMENT_TIMING_BUDGET			15//0 - ok,						1 - error during SetMeasurementTimingBudgetMicroSeconds
#define ODSSENSOR_ERROR_RANGING_SET_GPIO_CONFIG 					16//0 - ok,						1 - error during SetGpioConfig
#define ODSSENSOR_ERROR_START_MEASUREMENT							17//0 - ok,						1 - error during StartMeasurement
#define ODSSENSOR_ERROR_FLASH_CLEAR						18 //  set if occurs error during erasing flash memory
#define ODSSENSOR_ERROR_FLASH_ERR						19 //  set if occurs error during saving data to flash
#define ODSSENSOR_ERROR_FLASH_DIFF						20 //  set if saved value is different than it should be
#define ODSSENSOR_ERROR_CAN_BUFF_OVF					21 //  set if can buffer is overflowed

#endif /* ERRORFLAGS_H_ */
