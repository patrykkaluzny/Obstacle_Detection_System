#ifndef MAX44009EDT_H_
#define MAX44009EDT_H_
#include "main.h"
#include "stm32l4xx_hal.h"


//max44009edt adress
#define max44009edt_Adress                       (((uint8_t)0x4A)<< 1)

#define max$$009edt_I2C_Port  I2C1

// MAX44009 register definitions
#define max44009edt_Reg_InterruptStatus ((uint8_t)0x00)
#define max44009edt_Reg_InterruptEnable ((uint8_t)0x01)
#define max44009edt_Reg_Configuration ((uint8_t)0x02)
#define max44009edt_Reg_LuxHighByte ((uint8_t)0x03)
#define max44009edt_Reg_LuxLowByte ((uint8_t)0x04)
#define max44009edt_Reg_UpperThresholdHighByte ((uint8_t)0x05)
#define max44009edt_Reg_LowerThresholdHighByte ((uint8_t)0x06)
#define max44009edt_Reg_ThresholdTimer ((uint8_t)0x07)

// MAX44009 interrupt status end configuration definitions
#define max44009edt_INT_SET                       ((uint8_t)0x01) // Interrupt is asserted
#define max44009edt_INT_RESET                     ((uint8_t)0x00) // Interrupt is deasserted
#define max44009edt_INT_ENABLE                    ((uint8_t)0x01) // Interrupt enabled
#define max44009edt_INT_DISABLE                   ((uint8_t)0x00) // Interrupt disabled

// MAX44009 CFG register bits

#define max44009edt_CFG_CONT                      ((uint8_t)0x80) // Continuous mode
#define max44009edt_CFG_MANUAL                    ((uint8_t)0x40) // Manual configuration

// Current division ratio (CDR)
#define max44009edt_CDR_NORM                      ((uint8_t)0x00) // All photodiode current goes to the ADC
#define max44009edt_CDR_DIV8                      ((uint8_t)0x08) // Only 1/8 of the photodiode current goes to the ADC

// Integration time
#define max44009edt_IT_800ms                      ((uint8_t)0x00) // 800ms
#define max44009edt_IT_400ms                      ((uint8_t)0x01) // 400ms
#define max44009edt_IT_200ms                      ((uint8_t)0x02) // 200ms
#define max44009edt_IT_100ms                      ((uint8_t)0x03) // 100ms
#define max44009edt_IT_50ms                       ((uint8_t)0x04) // 50ms
#define max44009edt_IT_25ms                       ((uint8_t)0x05) // 25ms
#define max44009edt_IT_12d5ms                     ((uint8_t)0x06) // 12.5ms
#define max44009edt_IT_6d25ms                     ((uint8_t)0x07) // 6.25ms

// Bit mask for MODE and RANGE bits
#define max44009edt_MASK_CFG_MODE                 ((uint8_t)0xC0)

// Bit mask for CDR bit and integration time
#define max44009edt_MASK_CDR_IT                   ((uint8_t)0x0F)

// Value indicating overrange condition (used in return of GetLux() function)
#define max44009edt_OVERRANGE                     ((uint32_t)1000000000U)


//Functions prototypes
//int32_t max44009edt_GetLux(void);
void max44009edt_Write(uint8_t RegisterAdress, uint8_t RegisterValue);
uint8_t max44009edt_Read(uint8_t RegisterAdress);
int32_t max44009edt_ReadLux(void);
uint8_t max44009edt_INTStatus(void);
void max44009edt_INTEnable(void);
void max44009edt_INTDisable(void);
void max44009edt_SetModeAutomatic(void);
void max44009edt_SetModeContinuous(void);
void max44009edt_SetModeManual(uint8_t cdr, uint8_t tim);
void max44009edt_SetThrU(uint8_t value);
void max44009edt_SetThrL(uint8_t value);
void max44009edt_SetThrT(uint8_t value);
void max44009edt_Init(void);



#endif /* MAX44009EDT_H_ */
