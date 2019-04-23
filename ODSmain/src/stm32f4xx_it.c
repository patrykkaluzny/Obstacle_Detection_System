/************************* Description ******************************
* File Name			: stm32f4xx_it.c
* Author			:
* Version			: V1.0.0
* Date				: 28/07/2018
* Description		: Interrupt handlers
********************************************************************/

////// Includes //////
#include "stm32f4xx_it.h"
#include "main.h"
#include "gpio.h"
#include "can.h"
#include "structures.h"
#include "initSystemFunctions.h"
#include "CAN1_functions.h"
#include "CAN2_functions.h"
#include "CAN1flags.h"
#include "CAN2flags.h"

////// Standard includes //////
#include <string.h>
#include <stdint.h>

////// Global variables //////
extern CanTxMsg CAN1_sFrame;
extern CanRxMsg CAN1_rFrame;
extern CanTxMsg CAN2_sFrame;
extern CanRxMsg CAN2_rFrame;
extern int CAN1_mailbox;
extern int CAN2_mailbox;
extern volatile typ_CANTxBuffer CAN1TxBuffer;
extern volatile typ_CANTxBuffer CAN2TxBuffer;

extern typ_ODSsesnorData ID_list[MAX_NUMBER_OF_SENSOR_BOARDS];
extern volatile typ_ODSmainData ODSmainData;




/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f40xx.s/startup_stm32f427x.s).                         */
/******************************************************************************/


/**
 * @brief Interrupt routine from TIM6 timer overflow.
 * @details Main timer, blinking LED.
 * @author
 * @date 2018-06-28
 */
void TIM6_DAC_IRQHandler(void)  //distance sending interrupt, 10Hz
{
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
	{
		CAN1_SendDistance();
		CAN1_SendLidar();
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
	}
}



void CAN1_RX0_IRQHandler(void)
{
	//read can1
	if(CAN_GetITStatus(CAN1, CAN_IT_FMP0)!= RESET)
	{
		CAN_Receive(CAN1, CAN_FIFO0, &CAN1_rFrame);
		CAN1_Decode(&CAN1_rFrame); //read can1
		CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
	}
}
void CAN2_RX0_IRQHandler(void)
{
	//read can2
	if(CAN_GetITStatus(CAN2, CAN_IT_FMP0)!= RESET)
	{
		CAN_Receive(CAN2, CAN_FIFO0, &CAN2_rFrame);
		CAN_DecodeFrame(&CAN2_rFrame);
		CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);
	}
}


/**************** TIM8_TRG_COM_TIM14_IRQHandler *********************
* Function Name     : TIM8_TRG_COM_TIM14_IRQHandler
* Description       : CAN1 resend procedure
* Input             : None
* Output            : None
* Return            : None
********************************************************************/
void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM14, TIM_IT_Update) != RESET)
    {
        for(u8 i=0; i<3; i++)
        {
            u8 result = CAN1_ResendFrame(&CAN1TxBuffer.sFrameBuffer[CAN1TxBuffer.sFrameBufferTail]);
            if(result != CAN_TxStatus_NoMailBox)
            {
                CAN1TxBuffer.sFrameBufferTail++;

                if(CAN1TxBuffer.sFrameBufferTail >= _CAN_TX_BUFFER_SIZE)
                {
                    CAN1TxBuffer.sFrameBufferTail = 0;
                }
                if(CAN1TxBuffer.sFrameBufferTail == CAN1TxBuffer.sFrameBufferHead)
                {
                    break;
                }
            }else
            {
                break;
            }
        }

        if(CAN1TxBuffer.sFrameBufferTail == CAN1TxBuffer.sFrameBufferHead)
        {
            TIM_Cmd(TIM14, DISABLE);
            TIM14->CNT = 0;
            CAN1TxBuffer.sFrameBufferOVF = 0;
        }

        TIM_ClearITPendingBit(TIM14,TIM_IT_Update);               //clear flag
    }
}

/**************** TIM8_UP_TIM13_IRQHandler *********************
* Function Name     : TIM8_UP_TIM13_IRQHandler
* Description       : CAN2 resend procedure
* Input             : None
* Output            : None
* Return            : None
********************************************************************/

void TIM8_UP_TIM13_IRQHandler(void)
{
	 if(TIM_GetITStatus(TIM13, TIM_IT_Update) != RESET)
	    {
	        for(u8 i=0; i<3; i++)
	        {
	            u8 result = CAN2_ResendFrame(&CAN2TxBuffer.sFrameBuffer[CAN2TxBuffer.sFrameBufferTail]);
	            if(result != CAN_TxStatus_NoMailBox)
	            {
	                CAN2TxBuffer.sFrameBufferTail++;

	                if(CAN2TxBuffer.sFrameBufferTail >= _CAN_TX_BUFFER_SIZE)
	                {
	                    CAN2TxBuffer.sFrameBufferTail = 0;
	                }
	                if(CAN2TxBuffer.sFrameBufferTail == CAN2TxBuffer.sFrameBufferHead)
	                {
	                    break;
	                }
	            }else
	            {
	                break;
	            }
	        }

	        if(CAN2TxBuffer.sFrameBufferTail == CAN2TxBuffer.sFrameBufferHead)
	        {
	            TIM_Cmd(TIM13, DISABLE);
	            TIM13->CNT = 0;
	            CAN2TxBuffer.sFrameBufferOVF = 0;
	        }

	        TIM_ClearITPendingBit(TIM13,TIM_IT_Update);       //clear flag
	    }

}
/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/
void TIM7_IRQHandler(void) //it counts time for system initialization functions
{
	//it works, tested only with one ODSsensor
	//if there is no respond from ODSsesnor
	if(TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
	{
		if(ODSmainData.MeassureTime_IsGoing)
		{
			TIM_Cmd(TIM7, DISABLE);
			TIM7->CNT = 0;
			ID_list[ODSmainData.MeassureTime_CurrentID].meassuredTime = 0;//zero in MeasureTime_list means that there is no respond
			ODSmainData.MeassureTime_CurrentID++;//measure time of respond of next ODSesnor from ID_list
			MessureTime_SendFrame();

		}
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	}

}
/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}



/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}



/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
