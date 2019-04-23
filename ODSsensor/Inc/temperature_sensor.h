#ifndef TEMPERATURESENSOR_H_
#define TEMPERATURESENSOR_H_

#include "stm32l4xx_hal.h"
#include "main.h"

#define MinTemparature 0.0
#define MaxTemparature 50.0
#define mV_OfMinTemperature 2633
#define mV_OfMaxTemperature 1958


float Conversion_Voltage_To_Temperature (float Voltage);
float Conversion_ADC_To_Voltage(uint16_t ADC_Value);
float ReadTemperaure(void);

#endif /* TEMPERATURESENSOR_H_ */
