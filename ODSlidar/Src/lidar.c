/*
 * lidar.c
 *
 *  Created on: 22.12.2018
 *      Author: Patryk
 */

#include "lidar.h"
#include "i2c.h"
#include "main.h"
#include "structures.h"
#include "errorFlags.h"

extern I2C_HandleTypeDef hi2c1;
extern typ_LidarBoard LidarBoardData;

void LIDAR_Config(uint8_t configMode)
{
	switch(configMode)
	{
	case 0:														// Default mode, balanced performance
		LIDAR_Write(SIG_COUNT_VAL,0x80);							//default value of SIG_COUNT_VAL
		LIDAR_Write(ACQ_CONFIG_REG,0x08);							//default value of ACQ_CONFIG_REG
		LIDAR_Write(THRESHOLD_BYPASS,0x00);							//default value of THRESHOLD_BYPASS
		break;
	case 1: 														// Short range, high speed
		LIDAR_Write(SIG_COUNT_VAL,0x1d);
		LIDAR_Write(ACQ_CONFIG_REG,0x08);							//default value of ACQ_CONFIG_REG
		LIDAR_Write(THRESHOLD_BYPASS,0x00);							//default value of THRESHOLD_BYPASS
		break;
	case 2: 														// Default range, higher speed short range
		LIDAR_Write(SIG_COUNT_VAL,0x80);							//default value of SIG_COUNT_VAL
		LIDAR_Write(ACQ_CONFIG_REG,0x00);
		LIDAR_Write(THRESHOLD_BYPASS,0x00);							//default value of THRESHOLD_BYPASS
		break;
	case 3: 														// Maximum range
		LIDAR_Write(SIG_COUNT_VAL,0xff);
		LIDAR_Write(ACQ_CONFIG_REG,0x08);							//default value of ACQ_CONFIG_REG
		LIDAR_Write(THRESHOLD_BYPASS,0x00);							//default value of THRESHOLD_BYPASS
		break;
	case 4:															// High sensitivity detection, high erroneous measurements
		LIDAR_Write(SIG_COUNT_VAL,0x80);							//default value of SIG_COUNT_VAL
		LIDAR_Write(ACQ_CONFIG_REG,0x08);							//default value of ACQ_CONFIG_REG
		LIDAR_Write(THRESHOLD_BYPASS,0x80);
		break;
	case 5: 														// Low sensitivity detection, low erroneous measurements
		LIDAR_Write(SIG_COUNT_VAL,0x80);							//default value of SIG_COUNT_VAL
		LIDAR_Write(ACQ_CONFIG_REG,0x08);							//default value of ACQ_CONFIG_REG
		LIDAR_Write(THRESHOLD_BYPASS,0xb0);
		break;
	default:
		break;
	}
}
void LIDAR_ResetSensor()
{
	LIDAR_Write(ACQ_COMMAND,0x00);
}

void LIDAR_Write(uint16_t MemAddr,uint8_t pData)
{
	HAL_I2C_Mem_Write(&hi2c1,LIDAR_Address,MemAddr,1,&pData,1,HAL_MAX_DELAY);
}
uint16_t LIDAR_ReadResult(uint8_t BiasCorrection)
{
	uint8_t busyFlag=0x1;
	uint32_t busyCounter=0;
	//to achieve good performance at high measurement rates bias correction should be perform at the beginning of every 100 sequential measurement commands
	if (BiasCorrection) {
		LIDAR_Write(ACQ_COMMAND, 0x04);
	} else {
		LIDAR_Write(ACQ_COMMAND, 0x03);
	}


	while(busyFlag!=0x0)
	{
		busyFlag=LIDAR_Busy();
		if(busyCounter>9999)
		{
			break;
			SetBits(LidarBoardData.errorFlag,LIDAR_BUSY);
		}
	}
	if (!busyFlag) {
		uint8_t distanceRead[2];
		uint8_t cmd[1];
		cmd[0] = RESULT_REG;
		HAL_I2C_Master_Transmit(&hi2c1, LIDAR_Address, cmd, 1, 0x1000);
		HAL_I2C_Master_Receive(&hi2c1, LIDAR_Address, distanceRead, 2, 0x1000);
		return (distanceRead[0] << 8) | distanceRead[1];
	}
	return 0xFFFF;
}
uint8_t LIDAR_Busy() // 1 - lidar is busy taking measurement, 0 - lidar is ready for new command
{
	uint8_t readData[1];
	uint8_t cmd[1];
	cmd[0]=STATUS;
	HAL_I2C_Master_Transmit(&hi2c1, LIDAR_Address, cmd, 1, 0x1000);
	HAL_I2C_Master_Receive(&hi2c1, LIDAR_Address, readData, 1, 0x1000);
	return (readData[0] & (1 << BUSY_BIT)) != 0;
}
void configureLidar()
{
	uint8_t cmd[1];
	cmd[0]=0x04;
	HAL_I2C_Mem_Write(&hi2c1,LIDAR_Address,0x00,1,cmd,1,0x1000);
	//Configure default mode
	cmd[0]=0x80;
	HAL_I2C_Mem_Write(&hi2c1,LIDAR_Address,0x02,1,cmd,1,0x1000);
	cmd[0]=0x08;
	HAL_I2C_Mem_Write(&hi2c1,LIDAR_Address,0x04,1,cmd,1,0x1000);
	cmd[0]=0x00;
	HAL_I2C_Mem_Write(&hi2c1,LIDAR_Address,0x1c,1,cmd,1,0x1000);
}
