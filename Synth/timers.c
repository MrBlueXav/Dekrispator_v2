/**
 ******************************************************************************
 * File Name		: timers.c
 * Date				:
 * Author			: Xavier Halgand
 * Description		:
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include "timers.h"

#define CHECK_MSEC 		4 // Read hardware every x msec
#define PRESS_MSEC 		20 // Stable time before registering pressed
#define RELEASE_MSEC 	20 // Stable time before registering released


static uint32_t TimingDelay = 0;
static uint32_t TimingDelay1 = 0;
uint32_t 		LED_counter[4]; // time counter for blue LED

static uint8_t	Count = RELEASE_MSEC / CHECK_MSEC;
static bool 	DebouncedKeyPress = false; // This holds the debounced state of the key.
static bool 	Key_changed = false;
static bool 	Key_pressed = false;

/*----------------------------------------------------------------------------------------------*/

extern void ButtonPressed_action(void);
extern void ButtonReleased_action(void);

//---------------------------------------------------------------------------


/**
 * @brief  Decrements the TimingDelays variables.
 * 			Called by SysTick_Handler() in stm32f4xx_it.c
 * @param  None
 * @retval None
 */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0)
	{
		TimingDelay--;
	}
	if (TimingDelay1 != 0)
	{
		TimingDelay1--;
	}
}

//---------------------------------------------------------------------------

uint32_t getTime(void)
{
	return TimingDelay1;
}

void setTime(uint32_t val)
{
	TimingDelay1 = val;
}
/***********************************************************************************/
/**
 * @brief  Turns selected LED On for  a given duration.
 * @param  Led: Specifies the Led to be set on.
 *   This parameter can be one of following parameters:
 *     @arg LED4
 *     @arg LED3
 *     @arg LED5
 *     @arg LED6
 * @retval None
 */
void start_LED_On(Led_TypeDef Led, uint32_t duration)
{
	BSP_LED_On(Led);
	LED_counter[Led] = duration;
}
/*------------------------------------------------------------------------------------*/
/* Function called by SysTick_Handler()  */
void update_temporized_LED(Led_TypeDef Led)
{
	LED_counter[Led]--;
	if (LED_counter[Led] == 0) BSP_LED_Off(Led);
}

/***************************************************************************************************************************/
// Service routines called every CHECK_MSEC to
// debounce both edges

void DebounceUserButton(void) // Called by SysTick_Handler() in file stm32f4xx_it.c
{
	bool RawState;

	RawState = (bool)BSP_PB_GetState(BUTTON_KEY);

	if (RawState == DebouncedKeyPress) {
		// Set the timer which allows a change from current state.
		if (DebouncedKeyPress) Count = RELEASE_MSEC / CHECK_MSEC;
		else Count = PRESS_MSEC / CHECK_MSEC;

	} else {
		// Key has changed - wait for new state to become stable.
		if (--Count == 0) {
			// Timer expired - accept the change.
			DebouncedKeyPress = RawState;
			Key_changed = true;
			Key_pressed = DebouncedKeyPress;
			// And reset the timer.
			if (DebouncedKeyPress) // rising edge
			{
				Count = RELEASE_MSEC / CHECK_MSEC;
				ButtonPressed_action();
			}
			else // falling edge
			{
				Count = PRESS_MSEC / CHECK_MSEC;
				ButtonReleased_action();
			}
		}
	}
}
