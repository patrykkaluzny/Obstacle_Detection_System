/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define XSHUT_Pin GPIO_PIN_4
#define XSHUT_GPIO_Port GPIOA
#define VL53LX_INTERRUPT_Pin GPIO_PIN_5
#define VL53LX_INTERRUPT_GPIO_Port GPIOA
#define VL53LX_INTERRUPT_EXTI_IRQn EXTI9_5_IRQn
#define Temperature_Input_Pin GPIO_PIN_7
#define Temperature_Input_GPIO_Port GPIOA
#define INFO1_Pin GPIO_PIN_0
#define INFO1_GPIO_Port GPIOB
#define INFO2_Pin GPIO_PIN_1
#define INFO2_GPIO_Port GPIOB
#define LightSensor_Init_Pin GPIO_PIN_8
#define LightSensor_Init_GPIO_Port GPIOA
#define TCAN_NEN_Pin GPIO_PIN_4
#define TCAN_NEN_GPIO_Port GPIOB
#define ERROR_Pin GPIO_PIN_5
#define ERROR_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */
#define SetBits(variable,line)	variable |= (1<<line)				// set bit and don't change other bits
#define ResetBits(variable,line) variable &= ~(1<<line)				// reset bit and don't change other bits
#define NegationBits(variable,line) variable ^= (1<<line)			// negate bit and don't change other bits
#define ReadBitsSet(variable, line) ((variable) & (1<<(line)))		// read bit is 1
#define ReadBitsReset(variable, line) (!((variable) & (1<<(line))))	// read bit is 0

#define ClearVariable(variable) variable=0  // clears all bits , for errorVariable purpose


#define vl53lx		0 // 0 dla vl53l0x, 1 dla vl53l1x

#define _CAN_TX_BUFFER_SIZE				40

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
