/**
 ******************************************************************************
 * File Name          	: adsr.h
 * Author				: modified by Xavier Halgand
 * Date               	:
 * Description        	:
 ******************************************************************************
 */
/***************************************************/
/*! \class ADSR
    \brief STK ADSR envelope class.

    This Envelope subclass implements a
    traditional ADSR (Attack, Decay,
    Sustain, Release) envelope.  It
    responds to simple keyOn and keyOff
    messages, keeping track of its state.
    The \e state = ADSR::DONE after the
    envelope value reaches 0.0 in the
    ADSR::RELEASE state.

    by Perry R. Cook and Gary P. Scavone, 1995 - 2005.
 */
/***************************************************/

#ifndef STK_ADSR_H
#define STK_ADSR_H

/* Includes ------------------------------------------------------------------*/

#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include "CONSTANTS.h"

/* Exported types ------------------------------------------------------------*/

//! Envelope states.
enum { ATTACK, DECAY, SUSTAIN, RELEASE, DONE };

typedef struct
{
	float 	attackRate_;
	float 	decayRate_;
	float 	sustainLevel_;
	float 	releaseRate_;
	float 	value_;
	float	lastOutput_;
	float 	target_;
	float	rate_;
	int 	state_;
	uint32_t cnt_; // sample counter for on state


} ADSR_t ;


/* Exported functions --------------------------------------------------------*/

//! Default constructor.
void ADSR_init(ADSR_t *env);

//! Set target = 1, state = \e ADSR::ATTACK.
void ADSR_keyOn(ADSR_t *env);

//! Set target = 0, state = \e ADSR::RELEASE.
void ADSR_keyOff(ADSR_t *env);

//! Set the attack rate.
void ADSR_setAttackRate(ADSR_t *env, float rate);

//! Set the decay rate.
void ADSR_setDecayRate(ADSR_t *env, float rate);

//! Set the sustain level.
void ADSR_setSustainLevel(ADSR_t *env, float level);

//! Set the release rate.
void ADSR_setReleaseRate(ADSR_t *env, float rate);

//! Set the attack rate based on a time duration.
void ADSR_setAttackTime(ADSR_t *env, float time);

//! Set the decay rate based on a time duration.
void ADSR_setDecayTime(ADSR_t *env, float time);

//! Set the release rate based on a time duration.
void ADSR_setReleaseTime(ADSR_t *env, float time);

//! Set sustain level and attack, decay, and release time durations.
void ADSR_setAllTimes(ADSR_t *env, float aTime, float dTime, float sLevel, float rTime);

//! Set the target value.
void ADSR_setTarget(ADSR_t *env, float target);

//! Return the current envelope \e state (ATTACK, DECAY, SUSTAIN, RELEASE, DONE).
int ADSR_getState(ADSR_t *env) ;

//! Set to state = ADSR::SUSTAIN with current and target values of \e aValue.
void ADSR_setValue(ADSR_t *env, float value);

float ADSR_computeSample( ADSR_t *env );

void setGateTime(uint8_t val);
void AttTime_set(uint8_t val);
void DecTime_set(uint8_t val);
void SustLevel_set(uint8_t val);
void RelTime_set(uint8_t val);

/*********************************************************************************************************/
#endif
