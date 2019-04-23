
#include "max44009edt.h"
#include "i2c.h"
#include <math.h>
// Write new value to the MAX44009 register

void max44009edt_Write(uint8_t RegisterAdress, uint8_t RegisterValue) {
	HAL_I2C_Mem_Write(&hi2c1, max44009edt_Adress, RegisterAdress, 1,
			&RegisterValue, sizeof(RegisterValue), HAL_MAX_DELAY);
}
// Read value of the MAX44009 register

uint8_t max44009edt_Read(uint8_t RegisterAdress) {
	uint8_t RegisterValue = 0;
	HAL_I2C_Mem_Read(&hi2c1, max44009edt_Adress, RegisterAdress,
			sizeof(RegisterAdress), &RegisterValue, 1, 100);
	return RegisterValue;
}
int32_t max44009edt_ReadLux() {
	uint8_t DataFromSensor[2];
	uint32_t Lux = 0;
	HAL_I2C_Mem_Read(&hi2c1, max44009edt_Adress, max44009edt_Reg_LuxHighByte, 1,
			DataFromSensor, 2, 100);
	Lux = 1 << ((DataFromSensor[0] & 0xF0) >> 4);
	if (Lux == 32768) {
		// Overrange condition
		Lux = max44009edt_OVERRANGE;
	} else {
		// Maximum accuracy, formula: 2^(exponent) * mantissa * 0.045
		Lux *= ((DataFromSensor[0] & 0x0F) << 4) + (DataFromSensor[1] & 0x0F);
		Lux *= 45;
	}
	return Lux;
}
// Read MAX44009 interrupt status
// return:
//   max44009edt_INT_RESET - no interrupt trigger event has occurred
//   max44009edt_INT_SET - interrupt has been triggered
// note: INTS bit will be cleared after calling this function
uint8_t max44009edt_INTStatus(void) {
	return (max44009edt_Read(max44009edt_Reg_InterruptStatus)
			& max44009edt_INT_SET);
}

// Enable interrupt on INT pin
void max44009edt_INTEnable(void) {
	max44009edt_Write(max44009edt_Reg_InterruptEnable,
	max44009edt_INT_ENABLE);
}

// Disable interrupt on INT pin
// note: also clears INTS bit in the STATUS register
void max44009edt_INTDisable(void) {
	max44009edt_Write(max44009edt_Reg_InterruptEnable,
	max44009edt_INT_DISABLE);
}

// Configure IC for full automatic mode
// IC will perform measures every 800ms with automatic range selection
// note: this is default mode
void max44009edt_SetModeAutomatic(void) {
	uint8_t reg;
	reg = max44009edt_Read(max44009edt_Reg_Configuration);
	reg &= ~(max44009edt_CFG_CONT | max44009edt_CFG_MANUAL);
	max44009edt_Write(max44009edt_Reg_Configuration, reg);
}

// Configure IC for continuous mode
// IC will perform measures in continuous mode, which means
// that as soon as one reading done, a new one begins
// Range in this mode automatic, thus the integration time
// will be chosen by internal IC circuitry
// Thus, if the IC chooses the integration time of 100ms,
// the measurements will be performed every 100ms
void max44009edt_SetModeContinuous(void) {
	uint8_t reg;

	reg = max44009edt_Read(max44009edt_Reg_Configuration);
	reg |= max44009edt_CFG_CONT;
	reg &= ~max44009edt_CFG_MANUAL;
	max44009edt_Write(max44009edt_Reg_Configuration, reg);
}

// Configure IC for manual mode
// IC will perform measures in continuous mode and will use
// programmed by user values of CDR and integration time
// input:
//   cdr - new state of CDR (current division ratio), one of max44009edt_CDR_xx values
//   tim - new value of integration time, one of max44009edt_IT_xx values
void max44009edt_SetModeManual(uint8_t cdr, uint8_t tim) {
	uint8_t reg;

	reg = max44009edt_Read(max44009edt_Reg_Configuration);
	// Clear CONT, CDR and TIM bits of CFG register
	reg &=
			~(max44009edt_CFG_CONT | max44009edt_CDR_DIV8
					| max44009edt_IT_6d25ms);
	// Set MANUAL bit and configure new values of CDR and TIM[2:0] bits
	reg |= max44009edt_CFG_MANUAL | (cdr & max44009edt_CDR_DIV8)
			| (tim & max44009edt_IT_6d25ms);
	max44009edt_Write(max44009edt_Reg_Configuration, reg);
}

// Configure MAX44009 upper threshold
// input:
//   value - new value of the upper threshold
// note: for the explanation of that value refer to the datasheet
void max44009edt_SetThrU(uint8_t value) {
	max44009edt_Write(max44009edt_Reg_UpperThresholdHighByte, value);
}

// Configure MAX44009 lower threshold
// input:
//   value - new value of the lower threshold
// note: for the explanation of that value refer to the datasheet
void max44009edt_SetThrL(uint8_t value) {
	max44009edt_Write(max44009edt_Reg_LowerThresholdHighByte, value);
}

// Configure MAX44009 threshold timer
// input:
//   value - new value of the threshold timer
// note: for the explanation of that value refer to the datasheet
void max44009edt_SetThrT(uint8_t value) {
	max44009edt_Write(max44009edt_Reg_ThresholdTimer, value);
}

// Configure MAX44009 to its default state
void max44009edt_Init(void) {
	// Interrupt disabled
	max44009edt_INTDisable();
	// Default mode: measurements performed every 800ms
	// Auto range: CDR and integration time are automatically determined by
	//             the internal autoranging circuitry of the IC
	max44009edt_Write(max44009edt_Reg_Configuration, 0x03);
	// Upper threshold: maximum
	max44009edt_SetThrU(0xFF);
	// Lower threshold: minimum
	max44009edt_SetThrL(0x00);
	// Threshold timer: 25,5s
	max44009edt_SetThrT(0xFF);
}


