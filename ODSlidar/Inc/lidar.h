/*
 * lidar.h
 *
 *  Created on: 22.12.2018
 *      Author: Patryk
 */

#ifndef LIDAR_H_
#define LIDAR_H_

#include "stm32l4xx_hal.h"


#define LIDAR_Address (0x62<<1)

#define BUSY_BIT 				0

//lidar registers/////////////////////////////////////////////////
#define ACQ_COMMAND				0x00	//device command
#define STATUS					0x01	//system status
#define SIG_COUNT_VAL			0x02	//maximum acquisition count, initial value 0x80
#define ACQ_CONFIG_REG			0x04
#define VELOCITY				0x09
#define PEAK_CORR				0x0c
#define NOISE_PICK				0x0d
#define SIGNAL_STRENGHT			0x0e
#define FULL_DELAY_HIGH			0x0f
#define FULL_DELAY_LOW			0x10
#define OUTER_LOOP_COUNT		0x11
#define REF_COUNT_VAL			0x12
#define LAST_DELAY_HIGH			0x14
#define LAST_DELAY_LOW			0x15
#define UNIT_ID_HIGH			0x16
#define UNIT_ID_LOW				0x17
#define I2C_ID_HIGH				0x18
#define I2C_ID_LOW				0x19
#define I2C_SEC_ADDR			0x1a
#define THRESHOLD_BYPASS		0x1c
#define I2C_CONFIG				0x1e
#define COMMAND					0x40
#define MEASURE_DELAY			0x45
#define PEAK_BCK				0x4c
#define CORR_DATA				0x52
#define CORR_DATA_SIGN			0x53
#define ACQ_SETTINGS			0x5d
#define POWER_CONTROL			0x65
#define RESULT_REG				0x8f

//Lidar functions
void LIDAR_Write(uint16_t MemAddr,uint8_t pData);
uint8_t LIDAR_Busy();
void LIDAR_Config(uint8_t configMode);
void LIDAR_ResetSensor();
uint16_t LIDAR_ReadResult(uint8_t BiasCorrection);
void configureLidar();

#endif /* LIDAR_H_ */
