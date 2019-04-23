/***************************** Description **************************
* File Name			: gpio.h
* Author			:
* Version			: V1.0.0
* Date				: 28/06/2018
* Description		: GPIO operation
********************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

////// Includes //////
#include "main.h"

////// Defines //////
/*********************************************************
 ************************ Diodes *************************
 *********************************************************/
#define	_Diode_Inf1  		GPIO_Pin_0
#define	_Diode_Inf2			GPIO_Pin_1
#define	_Diode_Err			GPIO_Pin_4
#define _Diode_GPIO			GPIOB


#define _CAN_NEN_GPIO		GPIOB
#define _CAN_NEN_PIN		GPIO_Pin_5
/*********************************************************
 ************************** CAN1 ***********************
 *********************************************************/
#define _CAN1_RX           		GPIO_Pin_11
#define _CAN1_TX				GPIO_Pin_12
#define _CAN1_GPIO     			GPIOA

#define _CAN1_RX_SOURCE			GPIO_PinSource11
#define _CAN1_TX_SOURCE			GPIO_PinSource12


/*********************************************************
 ************************** CAN2 ***********************
 *********************************************************/
#define _CAN2_RX    			GPIO_Pin_12
#define _CAN2_TX				GPIO_Pin_13
#define _CAN2_GPIO     			GPIOB

#define _CAN2_RX_SOURCE			GPIO_PinSource12
#define _CAN2_TX_SOURCE			GPIO_PinSource13



////// Prototypes //////
void GPIO_Conf(void);

#endif /* GPIO_H_ */
