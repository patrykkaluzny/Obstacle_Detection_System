/***************************** Description **************************
* File Name			: main.c
* Author			:
* Version			: V1.0.0
* Date				: 28/06/2018
* Description		: Main operation
********************************************************************/

////// Includes //////
#include "main.h"
#include "gpio.h"
#include "rcc.h"
#include "tim.h"
#include "nvic.h"
#include "can.h"
#include "initSystemFunctions.h"
#include "structures.h"
#include "functions.h"
////// Standard includes //////
#include <string.h>
#include <stdint.h>

////// Global variables //////

//odsmain data structure
volatile typ_ODSmainData ODSmainData;

//odslidar data structure
typ_ODSlidarData ODSlidarData;

//odssensor data array
typ_ODSsesnorData ID_list[MAX_NUMBER_OF_SENSOR_BOARDS];

//id list variables
extern typ_ODSsesnorData ID_list[MAX_NUMBER_OF_SENSOR_BOARDS];


int main(void)
{
	RCC_Conf();
	GPIO_Conf();
	NVIC_Conf();

	GPIO_SetBits(_Diode_GPIO,_Diode_Inf1|_Diode_Inf2|_Diode_Err); //show process of initialization


	TIM_Conf();
	CAN_Conf();

	CAN_TurnOffPowerSaveMode();
	Clear_typODSsenosrData(&ODSmainData); //clear odsmain data structure before use


	//flash is no longer used
	//FLASH_Configuration();
	//FLASH_ClearIDData();
	//FLASH_ReadListOFIDs();

	GPIO_ResetBits(_Diode_GPIO,_Diode_Inf1|_Diode_Inf2|_Diode_Err); //end of initialization

	TIM_Cmd(TIM6, ENABLE);
	while (1)
	{

	}
}


