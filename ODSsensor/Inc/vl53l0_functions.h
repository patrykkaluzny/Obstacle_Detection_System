#ifndef VL53L0_FUNCTIONS_H_
#define VL53L0_FUNCTIONS_H_

#include "vl53l0x_api.h"

#define VL53L0_ADRESS 0x52
#define VL53L0X_COMMS_I2C 	1

VL53L0X_Error VL53L0_InitManufacturingCalibration(void);
VL53L0X_Error VL53L0_Init(void);
VL53L0X_Error VL5F3L0_IsSensorFound(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
VL53L0X_Error VL53L0_SetupContinousRanging(void);
VL53L0X_Error VL53L0_TemperateureRecalibration(void);
uint8_t VL53L0_IsTemperateureRecalibrationRequired(void);

#endif /* VL53L0_FUNCTIONS_H_ */
