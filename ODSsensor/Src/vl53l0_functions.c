#include "vl53l0_functions.h"
#include "i2c.h"
#include "stm32l4xx_hal.h"
#include "vl53l0x_api.h"
#include "structures.h"
#include "flash.h"
#include "temperature_sensor.h"
#include "errorFlags.h"
#include "stm32l4xx_hal.h"

volatile VL53L0X_RangingMeasurementData_t VL53L0_RangingData;
VL53L0X_RangingMeasurementData_t* pRangingMeasurementData;
uint32_t * pInterruptMaskStatus;
uint8_t isInitDone=0;
VL53L0X_Dev_t vl53l0_0;
VL53L0X_DEV vl53l0_dev = &vl53l0_0;
struct typ_VL53L0_InitData initData={0,0,0,0,0,0,0,0};
float calibratedTemeperature ;

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim7;

// board data structure
extern volatile typ_DataToSend							boardData;

VL53L0X_Error VL53L0_InitManufacturingCalibration(void) {

	// InitManufacturingCalibration MUST be call at a positive ambient temperature

	VL53L0X_Error status = VL53L0X_ERROR_NONE;

	//turn on sensor
	HAL_GPIO_WritePin(GPIOA, XSHUT_Pin, GPIO_PIN_SET);

	//complete sensor structure
	vl53l0_dev->I2cDevAddr = VL53L0_ADRESS;
	vl53l0_dev->comms_speed_khz = I2C_TRAN_HZ;
	vl53l0_dev->I2cHandle = &hi2c1;
	vl53l0_dev->comms_type = VL53L0X_COMMS_I2C;

	//WaitDeviceBooted
	HAL_Delay(1000);

	//init device
	status = VL53L0X_DataInit(vl53l0_dev);
	if (status)
	{
		HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
		SetBits(boardData.errorFlag, ODSSENSOR_ERROR_DATAINIT);
	}

	status = VL53L0X_StaticInit(vl53l0_dev);
	if (status)
	{
		HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
		SetBits(boardData.errorFlag, ODSSENSOR_ERROR_STATICINIT);
	}

	//  initial customer manufacturing calibration

	float initTemp=0; // should be stored in device after ReadTemperaure.

	//measuring init temperature
	/*
	HAL_ADC_Start(&hadc1);
	if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
		initTemp = ReadTemperaure();
		ResetBits(boardData.errorFlag, ODSSENSOR_ERROR_TEMP);
	} else {
		SetBits(boardData.errorFlag, ODSSENSOR_ERROR_TEMP);
	}
	*/
	initTemp = boardData.temperatureValue;
	calibratedTemeperature = initTemp;

	uint32_t  refSpadCount ;   // should be stored in device after PerformRefSpadManagement.
	uint8_t  isApertureSpads ; // should be stored in device after PerformRefSpadManagement.

	status = VL53L0X_PerformRefSpadManagement(vl53l0_dev,&refSpadCount,&isApertureSpads);
	if (status)
	{
		HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
		SetBits(boardData.errorFlag, ODSSENSOR_ERROR_REF_SPAD_MANAGEMENT);
	}

	uint8_t  vhvSettings;   // should be stored in device after PerformRefCalibration.
	uint8_t  phaseCal;	  // should be stored in device after PerformRefCalibration.

	status = VL53L0X_PerformRefCalibration(vl53l0_dev, &vhvSettings, &phaseCal);
	if (status)
	{
		HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
		SetBits(boardData.errorFlag, ODSSENSOR_ERROR_REF_CALIBRATION);
	}

	/*  OFFSET CALIBRATION
	 * Recommendation is to use a white (88%reflectance) target at 100mm, in a dark
	 * environment. Target distance can be changed depending on customer’s constraints,
	 * but it has to be chosen in the linear part of the ranging curve.
	 */
	FixPoint1616_t CalDistanceMilliMeter = 170.0;
	int32_t  offsetMicroMeter;   //should be stored in device after OffsetCalibration

	status  = VL53L0X_PerformOffsetCalibration(vl53l0_dev, CalDistanceMilliMeter, &offsetMicroMeter);
	if (status)
	{
		HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
		SetBits(boardData.errorFlag, ODSSENSOR_ERROR_OFFSET_CALIBRATION);
	}

	//XTALK CALIBRATION
	FixPoint1616_t XTalkCalDistance; //distance to be determined
	FixPoint1616_t  xTalkCompensationRateMegaCps = 1; // value for test
	// status = VL53L0X_PerformXTalkCalibration (vl53l0_dev,  XTalkCalDistance, &xTalkCompensationRateMegaCps);
	//  TODO
	/*
	if (status)
		{
			HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
			SetBits(boardData.errorFlag, ODSSENSOR_ERROR_XTALK_CALIBRATION);
		}
	*/
	// STORE VALUES IN DEVICE MEMORY

	initData.refSpadCount =refSpadCount;
	initData.isApertureSpads = isApertureSpads;
	initData.vhvSettings = vhvSettings;
	initData.phaseCal = phaseCal;
	initData.offsetMicroMeter = offsetMicroMeter;
	initData.xTalkCompensationRateMegaCps = xTalkCompensationRateMegaCps;
	initData.initTemp = initTemp;
	initData.isManufacturingInitDone=1;

	SaveInitDataVL53Lx();

	// store  initData

	return status;
}

VL53L0X_Error VL53L0_Init(void) {

	VL53L0X_Error status = VL53L0X_ERROR_NONE;

	//turn on sensor
	HAL_GPIO_WritePin(GPIOA, XSHUT_Pin, GPIO_PIN_SET);

	//complete sensor structure
	vl53l0_dev->I2cDevAddr = VL53L0_ADRESS;
	vl53l0_dev->comms_speed_khz = I2C_TRAN_HZ;
	vl53l0_dev->I2cHandle = &hi2c1;
	vl53l0_dev->comms_type = VL53L0X_COMMS_I2C;

	//WaitDeviceBooted
	HAL_Delay(1000);

	if(ReadInitDataVL53Lx())
	{

		calibratedTemeperature = initData.initTemp;

		//init device
		status = VL53L0X_DataInit(vl53l0_dev);
		if (status)
		{
			HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
			SetBits(boardData.errorFlag, ODSSENSOR_ERROR_DATAINIT);
		}

		status = VL53L0X_StaticInit(vl53l0_dev);
		if (status)
		{
			HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
			SetBits(boardData.errorFlag, ODSSENSOR_ERROR_STATICINIT);
		}

		status = VL53L0X_SetReferenceSpads (vl53l0_dev, initData.refSpadCount,initData.isApertureSpads);
		if (status)
		{
			HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
			SetBits(boardData.errorFlag, ODSSENSOR_ERROR_REF_SPAD_MANAGEMENT);
		}

		if(VL53L0_IsTemperateureRecalibrationRequired())
		{
			uint8_t  vhvSettings;
			uint8_t  phaseCal;


			calibratedTemeperature = boardData.temperatureValue;

			status = VL53L0X_PerformRefCalibration(vl53l0_dev, &vhvSettings, &phaseCal);
			if (status)
			{
				HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
				SetBits(boardData.errorFlag, ODSSENSOR_ERROR_REF_CALIBRATION);
			}
			status = VL53L0X_SetRefCalibration (vl53l0_dev, vhvSettings, phaseCal);
			if (status)
			{
				HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
				SetBits(boardData.errorFlag, ODSSENSOR_ERROR_REF_CALIBRATION);
			}
		}
		else
		{
			status = VL53L0X_SetRefCalibration (vl53l0_dev, initData.vhvSettings, initData.phaseCal);
			if (status)
			{
				HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
				SetBits(boardData.errorFlag, ODSSENSOR_ERROR_REF_CALIBRATION);
			}
		}
		status = VL53L0X_SetOffsetCalibrationDataMicroMeter (vl53l0_dev, initData.offsetMicroMeter);
		if (status)
		{
			HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
			SetBits(boardData.errorFlag, ODSSENSOR_ERROR_OFFSET_CALIBRATION);
		}
	}
	else
	{
		status =  VL53L0_InitManufacturingCalibration();
	}
	isInitDone = 1;
	return status ;
}

VL53L0X_Error VL5F3L0_IsSensorFound()
{
	uint16_t Id;
	VL53L0X_Error status;
	status = VL53L0X_RdWord(vl53l0_dev, VL53L0X_REG_IDENTIFICATION_MODEL_ID, &Id);
	if (status) {
	  return VL53L0X_ERROR_UNDEFINED;
	}
	if (Id == 0xEEAA) {
		return VL53L0X_ERROR_NONE;
	}
	else
	{
		return VL53L0X_ERROR_NOT_IMPLEMENTED;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	VL53L0X_Error status = VL53L0X_ERROR_NONE;

  if(GPIO_Pin==GPIO_PIN_5 && initData.isManufacturingInitDone && isInitDone)
  {

	  HAL_GPIO_TogglePin(GPIOB,INFO2_Pin); //callback entry diode info
	  VL53L0X_RangingMeasurementData_t t;
	  uint32_t  pMeasurementDataReady;
	  status = VL53L0X_GetMeasurementDataReady (vl53l0_dev, &pMeasurementDataReady);
	  if (status)
	  {
		  HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
		  SetBits(boardData.errorFlag, ODSSENSOR_ERROR_CALLBACK_GET_MEASUREMENT_DATA_READY);
	  }
	  if(pMeasurementDataReady)
	  {
		  status = VL53L0X_GetRangingMeasurementData (vl53l0_dev,  &t);
		  if (status)
		  {
			  HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
			  SetBits(boardData.errorFlag, ODSSENSOR_ERROR_CALLBACK_GET_RANGING_MEASUREMENT_DATA);
		  }
	  boardData.distanceValue=(uint32_t)t.RangeMilliMeter;
	  }

	  status = VL53L0X_ClearInterruptMask (vl53l0_dev, VL53L0X_REG_SYSTEM_INTERMEASUREMENT_PERIOD);
	  if (status)
	  {
		  HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
		  SetBits(boardData.errorFlag, ODSSENSOR_ERROR_CALLBACK_CLEAR_INTERRUPT_MASK);
	  }
  }
}

VL53L0X_Error VL53L0_SetupContinousRanging(void)
{
	//SET DEVICE MODE , SET_GPIO
	 VL53L0X_StopMeasurement(vl53l0_dev);
	VL53L0X_Error status = VL53L0X_ERROR_NONE;
	status = VL53L0X_SetDeviceMode(vl53l0_dev,VL53L0X_DEVICEMODE_CONTINUOUS_TIMED_RANGING);

	if (status)
	{
		HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
		SetBits(boardData.errorFlag, ODSSENSOR_ERROR_RANGING_SETUP_SET_DEVICE_MODE);
	}

	status = VL53L0X_SetInterMeasurementPeriodMilliSeconds (vl53l0_dev, 20);
	if (status)
	{
		HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
		SetBits(boardData.errorFlag, ODSSENSOR_ERROR_RANGING_INTER_MEASUREMENT_PERIOD);
	}

	status = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(vl53l0_dev,20000);
	if (status)
	{
		HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
		SetBits(boardData.errorFlag, ODSSENSOR_ERROR_RANGING_MEASUREMENT_TIMING_BUDGET);
	}

	uint8_t Pin;
	VL53L0X_DeviceModes pDeviceMode;
	VL53L0X_GpioFunctionality pFunctionality;
	VL53L0X_InterruptPolarity pPolarity;

	status = VL53L0X_GetGpioConfig (vl53l0_dev, 0 , &pDeviceMode, &pFunctionality,&pPolarity);
	if (status)
	{
		HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
	}

	status =  VL53L0X_SetGpioConfig (vl53l0_dev, 0, VL53L0X_DEVICEMODE_CONTINUOUS_TIMED_RANGING,VL53L0X_GPIOFUNCTIONALITY_NEW_MEASURE_READY, VL53L0X_INTERRUPTPOLARITY_LOW);
	if (status)
	{
		HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
		SetBits(boardData.errorFlag, ODSSENSOR_ERROR_RANGING_SET_GPIO_CONFIG);
	}

	VL53L0X_DeviceError *error=NULL;
	status = VL53L0X_StartMeasurement(vl53l0_dev);
	if (status)
	{
		HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
		SetBits(boardData.errorFlag, ODSSENSOR_ERROR_START_MEASUREMENT);
	}

	status=VL53L0X_GetDeviceErrorStatus(vl53l0_dev,error);

	return status;
}

VL53L0X_Error VL53L0_TemperateureRecalibration(void)
{
	//This function should be called every 8 deg temperature diff
	VL53L0X_Error status = VL53L0X_ERROR_NONE;
	uint8_t  vhvSettings;
	uint8_t  phaseCal;
	calibratedTemeperature = boardData.temperatureValue;
	// need global variable to store temperature for which function was called

	status = VL53L0X_StopMeasurement(vl53l0_dev);
	if (status) {HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);}
	//HAL_Delay(1);
	status = VL53L0X_PerformRefCalibration(vl53l0_dev, &vhvSettings, &phaseCal);
	if (status) {HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);}
	status = VL53L0X_SetRefCalibration(vl53l0_dev, vhvSettings, phaseCal);
	if (status) {HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);}
	status = VL53L0X_StartMeasurement(vl53l0_dev);
		if (status) {HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);}

	return status ;
}

uint8_t VL53L0_IsTemperateureRecalibrationRequired(void)
{
	if((calibratedTemeperature - boardData.temperatureValue)>8 || (calibratedTemeperature - boardData.temperatureValue)<(-8) )
		return 1;
	else
		return 0;

}


