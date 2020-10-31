/**
 ******************************************************************************
 * @file    main.c
 * @author	Xavier Halgand
 * @version
 * @date
 * @brief   Dekrispator_v2 main file
 ******************************************************************************
 *
 *
 ******************************************************************************
 */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/*---------------------------------------------------------------------------*/

USBH_HandleTypeDef hUSBHost; /* USB Host handle */

MIDI_ApplicationTypeDef Appli_state = APPLICATION_IDLE;

bool demoMode = true;
bool freeze = false;
bool sequencerIsOn = true;
extern ADSR_t adsr;

/*---------------------------------------------------------------------------*/
static void SystemClock_Config(void);
static void USBH_UserProcess_callback(USBH_HandleTypeDef *pHost, uint8_t vId);
/*----------------------------------------------------------------------------*/

void ButtonPressed_action(void)
{ // User butter toggles sequencer
	sequencerIsOn = !sequencerIsOn;
	if (!sequencerIsOn)
		ADSR_keyOff(&adsr);
	Reset_notes_On();
	BSP_LED_Toggle(LED_Red);
}
/*----------------------------------------------------------------------------*/
void ButtonReleased_action(void)
{
	// nothing to do
}

/*====================================================================================================*/

int main(void)
{

	HAL_Init();

	/* Initialize LEDs mounted on STM32F4-Discovery board */
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);
	BSP_LED_Init(LED6);

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize User Button */
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);

	/* Initialize the on-board random number generator ! */
	randomGen_init();

	Synth_Init();
	audio_init();

	/*## Init Host Library ################################################*/
	USBH_Init(&hUSBHost, USBH_UserProcess_callback, 0);

	/*## Add Supported Class ##############################################*/
	USBH_RegisterClass(&hUSBHost, USBH_MIDI_CLASS);

	/*## Start Host Process ###############################################*/
	USBH_Start(&hUSBHost);

	while (1)
	{
		MIDI_Application();

		/* USBH_Background Process */
		USBH_Process(&hUSBHost);
	}
}
/*====================================================================================================*/
/**
 * @brief  User Process function callback
 * @param  phost: Host Handle
 * @param  id: Host Library user message ID
 * @retval none
 */
static void USBH_UserProcess_callback(USBH_HandleTypeDef *pHost, uint8_t vId)
{
	switch (vId)
	{
	case HOST_USER_SELECT_CONFIGURATION:
		break;

	case HOST_USER_DISCONNECTION:
		Appli_state = APPLICATION_DISCONNECT;
		BSP_LED_Off(LED_Green);
		BSP_LED_Off(LED_Blue);
		break;

	case HOST_USER_CLASS_ACTIVE:
		Appli_state = APPLICATION_READY;
		BSP_LED_On(LED_Green);
		BSP_LED_Off(LED_Blue);
		//BSP_LED_Off(LED_Red);
		break;

	case HOST_USER_CONNECTION:
		Appli_state = APPLICATION_START;
		BSP_LED_On(LED_Blue);
		break;

	default:
		break;
	}
}
/*----------------------------------------------------------------------------------------------*/

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 168000000
 *            HCLK(Hz)                       = 168000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 4
 *            APB2 Prescaler                 = 2
 *            HSE Frequency(Hz)              = 8000000
 *            PLL_M                          = 8
 *            PLL_N                          = 336
 *            PLL_P                          = 2
 *            PLL_Q                          = 7
 *            VDD(V)                         = 3.3
 *            Main regulator output voltage  = Scale1 mode
 *            Flash Latency(WS)              = 5
 * @param  None
 * @retval None
 */
static void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable Power Control clock */
	__PWR_CLK_ENABLE();

	/* The voltage scaling allows optimizing the power consumption when the device is
	 clocked below the maximum system frequency, to update the voltage scaling value
	 regarding system frequency refer to product datasheet.  */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	{
		Error_Handler();
	}
}

/*----------------------------------------------------------------------------------------------*/

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
void Error_Handler(void)
{
	/* Turn LED5 on */
	BSP_LED_On(LED_Red);
	while (1)
	{
	}
}

/*----------------------------------------------------------------------------------------------*/

/**
 * @brief  EXTI line detection callbacks.
 * @param  GPIO_Pin: Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/*****************************END OF FILE******************************************/
