/***************************** Description **************************
 * File Name			: tim.c
 * Author			:
 * Version			: V1.0.0
 * Date				: 28/06/2018
 * Description		: Timer operation
 ********************************************************************/

////// Includes //////
#include "tim.h"

////// Declarations //////
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

/**
 * @brief TIM initialisation function.
 * @details
 * @author
 * @date 2018-06-28
 */
void TIM_Conf() {
	/******************************************************
	 ***************** TIM6 configuration *****************
	 ******************************************************/
	TIM_TimeBaseInitStructure.TIM_Period = _TIM_6_Period;
	TIM_TimeBaseInitStructure.TIM_Prescaler = _TIM_6_Scal;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);
	TIM_ClearITPendingBit(TIM6, TIM_IT_Update);

	TIM_ARRPreloadConfig(TIM6, ENABLE);			//
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);  //

	//TIM_Cmd(TIM6, ENABLE);
	/******************************************************
	 ********** TIM14 configuration, CAN1 resend ***********
	 ******************************************************/
	TIM_TimeBaseInitStructure.TIM_Period = _TIM_14_Period;
	TIM_TimeBaseInitStructure.TIM_Prescaler = _TIM_14_Scal;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStructure);
	TIM_ClearITPendingBit(TIM14, TIM_IT_Update);
	TIM_ARRPreloadConfig(TIM14, ENABLE);                    // Automatic preload
	TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);   // Enable interrupt generating

	//TIM_Cmd(TIM14, ENABLE);               // Timer enabled during resends procedure


	/******************************************************
	********** TIM13 configuration, CAN2 resend ***********
	******************************************************/
	TIM_TimeBaseInitStructure.TIM_Period = _TIM_13_Period;
	TIM_TimeBaseInitStructure.TIM_Prescaler = _TIM_13_Scal;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM13, &TIM_TimeBaseInitStructure);
	TIM_ClearITPendingBit(TIM13, TIM_IT_Update);
	TIM_ARRPreloadConfig(TIM13, ENABLE);                    // Automatic preload
	TIM_ITConfig(TIM13, TIM_IT_Update, ENABLE);   // Enable interrupt generating

	//TIM_Cmd(TIM13, ENABLE);               // Timer enabled during resends procedure

	/******************************************************
	***************** TIM7 configuration *****************
	******************************************************/
	TIM_TimeBaseInitStructure.TIM_Period = _TIM_7_Period;
	TIM_TimeBaseInitStructure.TIM_Prescaler = _TIM_7_Scal;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStructure);
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);

	TIM_ARRPreloadConfig(TIM7, ENABLE);			// Automatic preload
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);  // Enable interrupt generating
	TIM_Cmd(TIM7,DISABLE);
	//TIM_Cmd(TIM7, ENABLE);								//timer enabled during time measuring procedure
}

