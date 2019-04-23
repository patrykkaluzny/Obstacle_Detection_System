/***************************** Description **************************
* File Name			: rcc.c
* Author			:
* Version			: V1.0.0
* Date				: 28/06/2018
* Description		: RCC operation
********************************************************************/

////// Includes //////
#include "rcc.h"
#include "main.h"
#include "stm32f4xx.h"

/**
 * @brief RCC initialisation function.
 * @details
 * @author
 * @date 2018-06-28
 */
void RCC_Conf(void)
{
	// AHB1
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE);
	// AHB2

	// APB1
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

	// APB2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);


}
