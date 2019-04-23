/***************************** Description **************************
 * File Name			: gpio.c
 * Author			:
 * Version			: V1.0.0
 * Date				: 28/06/2018
 * Description		: GPIO operation
 ********************************************************************/

////// Includes //////
#include "gpio.h"

////// Definitions //////
GPIO_InitTypeDef GPIO_InitStructure;

/**
 * @brief GPIO initialisation function.
 * @details
 * @author
 * @date 2018-06-28
 */
void GPIO_Conf(void) {
	/*********************************************************
	 ******************** Konfiguracja Diod ******************
	 *********************************************************/
	// Configure Diodes
	GPIO_InitStructure.GPIO_Pin = _Diode_Inf1 | _Diode_Inf2 | _Diode_Err;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(_Diode_GPIO, &GPIO_InitStructure);
	//Configure CAN_NEN
	GPIO_InitStructure.GPIO_Pin = _CAN_NEN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(_CAN_NEN_GPIO, &GPIO_InitStructure);

	/*********************************************************
	 **************** Konfiguracja we/wy CAN1 ***************
	 *********************************************************/

	/* Configure CAN RX and TX pins */
	GPIO_InitStructure.GPIO_Pin = _CAN1_RX | _CAN1_TX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(_CAN1_GPIO, &GPIO_InitStructure);


	GPIO_PinAFConfig(_CAN1_GPIO, _CAN1_RX_SOURCE, GPIO_AF_CAN1);
	GPIO_PinAFConfig(_CAN1_GPIO, _CAN1_TX_SOURCE, GPIO_AF_CAN1);

	/*********************************************************
	 **************** Konfiguracja we/wy CAN2 ***************
	 *********************************************************/

	/* Configure CAN RX and TX pins */
	GPIO_InitStructure.GPIO_Pin = _CAN2_RX | _CAN2_TX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(_CAN2_GPIO, &GPIO_InitStructure);


	GPIO_PinAFConfig(_CAN2_GPIO, _CAN2_RX_SOURCE, GPIO_AF_CAN2);
	GPIO_PinAFConfig(_CAN2_GPIO, _CAN2_TX_SOURCE, GPIO_AF_CAN2);


}
