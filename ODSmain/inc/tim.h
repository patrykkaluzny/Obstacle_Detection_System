/***************************** Description **************************
* File Name			: tim.h
* Author			:
* Version			: V1.0.0
* Date				: 28/06/2018
* Description		: Timer operation
********************************************************************/

#ifndef TIM_H_
#define TIM_H_

////// Includes //////
#include "main.h"


////// Defines //////
// TIM6 - main timer
#define _TIM_6_Scal			4499					// Clock divider 90000000/4500 = 20kHz
#define _TIM_6_Period		399						// Period 20kHz/400 = 50Hz, 20ms
// TIM14 - CAN1 buffer timer
#define _TIM_14_Scal        89                      // Clock divider 90000000/90 = 1MHz
#define _TIM_14_Period      149                     // Period 1MHz/150 = 6.6666kHz, 150us
// TIM13 - CAN2 buffer timer
#define _TIM_13_Scal        89                      // Clock divider 90000000/90 = 1MHz
#define _TIM_13_Period      149                     // Period 1MHz/150 = 6.6666kHz, 150us
// TIM7 - time measure to sort ODSsensor boards
#define _TIM_7_Scal			14						// Clock divider 90000000/15 = 6MHz
#define _TIM_7_Period		59999				// Period 6MHz/60000 = 100Hz, 10ms
////// Prototypes //////
void TIM_Conf(void);

#endif /* TIM_H_ */
