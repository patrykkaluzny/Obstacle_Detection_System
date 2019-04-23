#include "vl53l1_functions.h"
#include "i2c.h"
#include "stm32l4xx_hal.h"

volatile VL53L1_RangingMeasurementData_t VL53L1_RangingData;
extern I2C_HandleTypeDef hi2c1;
VL53L1_Dev_t 			vl53l1_0;
VL53L1_DEV 				vl53l1_dev=&vl53l1_0;

VL53L1_Error VL53L1_Init(void)
{

	VL53L1_Error status=VL53L1_ERROR_NONE;
	VL53L1_DeviceInfo_t info;
	VL53L1_State stan; //lalalalala
	//turn on sensor
	HAL_GPIO_WritePin(GPIOA, XSHUT_Pin,GPIO_PIN_SET);

	//complete sensor structure
	vl53l1_dev->I2cDevAddr=VL53L1_ADRESS;
	vl53l1_dev->comms_speed_khz=400;
	vl53l1_dev->comms_type=VL53L1_I2C;
	vl53l1_dev->I2cHandle=&hi2c1;
	//vl53l1_dev->new_data_ready_poll_duration_ms=250;
	status=VL53L1_GetPalState(vl53l1_dev, &stan);
	if(stan)
	{
		while(1);
	}
	status=VL53L1_GetDeviceInfo(vl53l1_dev,&info);
	//init device
	status = VL53L1_WaitDeviceBooted(vl53l1_dev);
	status=VL53L1_GetPalState(vl53l1_dev, &stan);
		if(stan)
		{
			while(1);
		}
	if(status)
		{
			//error
			HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
			while(1);
		}
	//status = VL53L1_DataInit(vl53l1_dev);
	if(status)
		{
			//error
			HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
			while(1);
		}
	status = VL53L1_StaticInit(vl53l1_dev);
	if(status)
		{
			//error
			HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
			while(1);
		}


/*	status = VL53L1_SetDistanceMode(vl53l1_dev, VL53L1_DISTANCEMODE_LONG);
	status = VL53L1_SetMeasurementTimingBudgetMicroSeconds(vl53l1_dev, 50000);
	status = VL53L1_SetInterMeasurementPeriodMilliSeconds(vl53l1_dev, 250);
	status = VL53L1_StartMeasurement(vl53l1_dev);*/
	if(status)
	{
		//error
		HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
		while(1);
	}
	return status;
}

