/**
 ******************************************************************************
 * @file     Dekrispator  stm32f4xx_it.c
 * @author  Bluexav + MCD Application Team
 * @version V1.1.0
 * @date    26-June-2014
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and
 *          peripherals interrupt service routine.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
 *
 * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "timers.h"

/** @addtogroup STM32F4-Discovery_Audio_Player_Recorder
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

extern I2S_HandleTypeDef hAudioOutI2s;

extern I2S_HandleTypeDef hAudioInI2s;
__IO uint32_t TimeRecBase = 0; /* Time Recording base variable */

extern HCD_HandleTypeDef hHCD;
extern bool demoMode;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void) {
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void) {
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1) {
	}
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void) {
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1) {
	}
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void) {
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1) {
	}
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void) {
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1) {
	}
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void) {
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void) {
}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void) {
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void) {
	HAL_IncTick();

	TimingDelay_Decrement();
	update_temporized_LED(LED_Blue);
	//if (demoMode == true)
	DebounceUserButton();

}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f40xx.s).                                              */
/******************************************************************************/

/**
 * @brief  This function handles External line 0 interrupt request.
 * @param  None
 * @retval None
 */
void EXTI0_IRQHandler(void) {
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

/**
 * @brief  This function handles External line 1 interrupt request.
 * @param  None
 * @retval None
 */
void EXTI1_IRQHandler(void) {
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}

/**
 * @brief  This function handles main I2S interrupt.
 * @param  None
 * @retval 0 if correct communication, else wrong communication
 */
void I2S3_IRQHandler(void) {
	HAL_DMA_IRQHandler(hAudioOutI2s.hdmatx);
}

/**
 * @brief  This function handles DMA Stream interrupt request.
 * @param  None
 * @retval None
 */
void I2S2_IRQHandler(void) {
	HAL_DMA_IRQHandler(hAudioInI2s.hdmarx);
}

/**
 * @brief  This function handles TIM4 global interrupt request.
 * @param  None
 * @retval None
 */
void TIM4_IRQHandler(void) {
	//HAL_TIM_IRQHandler(&hTimLed);
}

/**
 * @brief  This function handles USB-On-The-Go FS global interrupt request.
 * @param  None
 * @retval None
 */
void OTG_FS_IRQHandler(void) {
	HAL_HCD_IRQHandler(&hHCD);

}

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
