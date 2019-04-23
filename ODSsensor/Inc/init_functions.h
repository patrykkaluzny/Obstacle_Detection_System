#ifndef INIT_FUNCTIONS_H_
#define INIT_FUNCTIONS_H_

#include "main.h"
#include "stm32l4xx_hal.h"

/**
 * The STM32 factory-programmed UUID memory.
 * Three values of 32 bits each starting at this address
 * Use like this: STM32_UUID[0], STM32_UUID[1], STM32_UUID[2]
 */

#define STM32_UUID ((uint32_t *)0x1FFF7590)  // its returns array with serialID
/*
STM32_UUID[0] - Bits 31:0 (UID[31:0]) - coordinates on the wafer
STM32_UUID[1] - Bits 31:8 (UID[63:40]) - LOT_NUM[23:0] Lot number  (ASCII encoded), Bits 7:0 (UID[39:32]): WAF_NUM[7:0]Wafer number (8-bit unsigned number)
STM32_UUID[2] - Bits 31:0 (UID[95:64]) - LOT_NUM[55:24] Lot number (ASCII encoded) */

void SendDeviceSerailID();
void InitODSsensor();
void FirstTemp();

#endif /* INIT_FUNCTIONS_H_ */
