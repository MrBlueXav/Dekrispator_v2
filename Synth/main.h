/**
 ******************************************************************************
 * @file    main.h
 * Author: 	Xavier Halgand
 * @author
 * @version
 * @date
 * @brief   Header for main.c module
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* Local includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_audio.h"
#include "stm32f4_discovery_accelerometer.h"
#include <stdio.h>
#include "stm32f4xx_it.h"
#include "lis302dl.h"

#include "usbh_MIDI.h"
#include "MIDI_application.h"
#include "timers.h"
#include "soundGen.h"
#include "audio_conf.h"
#include "delay.h"
#include "chorusFD.h"
#include "random.h"
#include "CONSTANTS.h"
#include "drifter.h"
#include "resonantFilter.h"
#include "adsr.h"
#include "sequencer.h"

/* Exported functions ------------------------------------------------------- */
void Error_Handler(void);

/*-------------------------------------------------------*/
#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
