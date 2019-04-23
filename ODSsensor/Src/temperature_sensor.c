#include "temperature_sensor.h"
#include "adc.h"

extern ADC_HandleTypeDef hadc1;

float Conversion_ADC_To_Voltage(uint16_t ADC_Value) {
	return 3.3 * (float) ADC_Value / 4095.0;
}
float Conversion_Voltage_To_Temperature(float Voltage) {
	float x = (mV_OfMinTemperature - mV_OfMaxTemperature) / (MinTemparature - MaxTemparature);
	return (Voltage * 1000 - mV_OfMinTemperature + x * MinTemparature) / x;
}
float ReadTemperaure(void) {
	int16_t ADC_Value;
	ADC_Value= HAL_ADC_GetValue(&hadc1);
	return Conversion_Voltage_To_Temperature(Conversion_ADC_To_Voltage(ADC_Value));
}
