/**
 ******************************************************************************
 * File Name          : audio_conf.h
 * Author				: Xavier Halgand
 * Date               :
 * Description        :
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AUDIO_CONF_H
#define __AUDIO_CONF_H


/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include "CONSTANTS.h"
#include "stm32f4_discovery_audio.h"
#include "stm32f4_discovery.h"
#include "soundGen.h"
#include "main.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  BUFFER_OFFSET_NONE = 0,
  BUFFER_OFFSET_HALF,
  BUFFER_OFFSET_FULL,
}BUFFER_StateTypeDef;

/* Exported functions ------------------------------------------------------- */
void audio_init(void);
void toggleSound(void);
void incVol(void);
void decVol(void);
void Volume_set(uint8_t val);



#endif /* __AUDIO_H */
