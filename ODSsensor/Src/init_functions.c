#include "init_functions.h"
#include "CANflags.h"
#include "can.h"
#include "main.h"
#include <stdint.h>
#include "errorFlags.h"
#include "structures.h"
#include "temperature_sensor.h"

extern ADC_HandleTypeDef hadc1;
uint8_t ODS_Id;
extern volatile typ_DataToSend							boardData;
void SendDeviceSerailID() //it works
{
    uint32_t idPart1 = STM32_UUID[0]; // Bits 31:0 (UID[31:0]) - coordinates on the wafer
    uint32_t idPart2 = STM32_UUID[1]; // Bits 31:8 (UID[63:40]) - LOT_NUM[23:0] Lot number  (ASCII encoded), Bits 7:0 (UID[39:32]): WAF_NUM[7:0]Wafer number (8-bit unsigned number)
    CAN_SendFrameWithBuffer(_CAN_INIT_SERIAL,&idPart1,&idPart2);
}
void FirstTemp()
{
	HAL_ADC_Start(&hadc1);
	if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
			boardData.temperatureValue = ReadTemperaure();
			ResetBits(boardData.errorFlag, ODSSENSOR_ERROR_TEMP);
		} else {
			SetBits(boardData.errorFlag, ODSSENSOR_ERROR_TEMP);
		}
}



