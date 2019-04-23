/***************************** Description **************************
* File Name			: main.h
* Author			:
* Version			: V1.0.0
* Date				: 28/06/2018
* Description		: Main operation
********************************************************************/

#ifndef MAIN_H_
#define MAIN_H_

////// Includes //////
#include "stm32f4xx.h"

////// Defines //////

#define _CAN_TX_BUFFER_SIZE				100

#define MAX_NUMBER_OF_SENSOR_BOARDS 16

/*********************************************************
 ************************ Macros *************************
 *********************************************************/
#define SetBits(variable,line)	variable |= (1<<line)				// set bit and don't change other bits
#define ResetBits(variable,line) variable &= ~(1<<line)				// reset bit and don't change other bits
#define NegationBits(variable,line) variable ^= (1<<line)			// negate bit and don't change other bits
#define ReadBitsSet(variable, line) ((variable) & (1<<(line)))		// read bit is 1
#define ReadBitsReset(variable, line) (!((variable) & (1<<(line))))	// read bit is 0

#define ClearVariable(variable) variable=0  // clears all bits , for flags purpose

#endif /* MAIN_H_ */
