/**
 ******************************************************************************
 * File Name          	: adsr.c
 * Author				: modified by Xavier Halgand
 * Date               	:
 * Description        	:
 ******************************************************************************
 */

/***************************************************/
/*
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
/***************************************************/

#include "adsr.h"

/*---------------------------------------------------------------------------*/

ADSR_t			adsr _CCM_;

/*---------------------------------------------------------------------------*/

void ADSR_init(ADSR_t *env)
{
  env->target_ = 0.0;
  env->value_ = 0.0;
  env->attackRate_ = 0.001;
  env->decayRate_ = 0.001;
  env->sustainLevel_ = 0.5;
  env->releaseRate_ = 0.01;
  env->state_ = ATTACK;
  env->cnt_ = 0;
  //env->gateTime_ = 10000;
}

void ADSR_keyOn(ADSR_t *env)
{
	env->cnt_ = 0;
	env->target_ = 1.0f;
	env->rate_ = 	env->attackRate_;
	env->state_ = ATTACK;
}

void ADSR_keyOff(ADSR_t *env)
{
	env->cnt_ = 0;
	env->target_ = 0.0;
	env->rate_ = 	env->releaseRate_;
	env->state_ = RELEASE;
}

void ADSR_setAttackRate(ADSR_t *env, float rate)
{
	env->attackRate_ = rate;
}

void ADSR_setDecayRate(ADSR_t *env, float rate)
{
	env->decayRate_ = rate;
}

void ADSR_setSustainLevel(ADSR_t *env, float level)
{
	env->sustainLevel_ = level;
}

void ADSR_setReleaseRate(ADSR_t *env, float rate)
{
	env->releaseRate_ = rate;
}

void ADSR_setAttackTime(ADSR_t *env, float time)
{
	env->attackRate_ = 1.0 / ( time * SAMPLERATE );
}

void ADSR_setDecayTime(ADSR_t *env, float time)
{
	env->decayRate_ = 1.0 / ( time * SAMPLERATE );
}

void ADSR_setReleaseTime(ADSR_t *env, float time)
{
	env->releaseRate_ = env->sustainLevel_ / ( time * SAMPLERATE );
}

void ADSR_setAllTimes(ADSR_t *env, float aTime, float dTime, float sLevel, float rTime)
{
  ADSR_setAttackTime(env, aTime);
  ADSR_setDecayTime(env, dTime);
  ADSR_setSustainLevel(env, sLevel);
  ADSR_setReleaseTime(env, rTime);
}

void ADSR_setTarget(ADSR_t *env, float target)
{
	env->target_ = target;
  if (env->value_ < env->target_) {
	  env->state_ = ATTACK;
	  ADSR_setSustainLevel(env, env->target_);
    env->rate_ = env->attackRate_;
  }
  if (env->value_ > env->target_) {
	  ADSR_setSustainLevel(env, env->target_);
    env->state_ = DECAY;
    env->rate_ = env->decayRate_;
  }
}

void ADSR_setValue(ADSR_t *env, float value)
{
	env->state_ = SUSTAIN;
	env->target_ = value;
	env->value_ = value;
	ADSR_setSustainLevel(env, value);
	env->rate_ = 0.0f;
}

int ADSR_getState(ADSR_t *env)
{
  return env->state_;
}

void AttTime_set(uint8_t val)
{
	ADSR_setAttackTime(&adsr, val/MIDI_MAX + 0.0001f);
}
void DecTime_set(uint8_t val)
{
	ADSR_setDecayTime(&adsr, .2*val/MIDI_MAX + 0.0001f);
}
void SustLevel_set(uint8_t val)
{
	ADSR_setSustainLevel(&adsr, val/MIDI_MAX);
}
void RelTime_set(uint8_t val)
{
	ADSR_setReleaseTime(&adsr, .5f * val/MIDI_MAX + 0.0001f);
}
/*--------------------------------------------------------------------------------------*/
float ADSR_computeSample(ADSR_t *env)
{
	(env->cnt_)++;

	switch (env->state_) {

  case ATTACK:
	  env->value_ += env->rate_;
    if (env->value_ >= env->target_)
    {
    	env->value_ = env->target_;
    	env->rate_ = env->decayRate_;
    	env->target_ = env->sustainLevel_;
    	env->state_ = DECAY;
    }
    break;

  case DECAY:
	  env->value_ -= env->decayRate_;
    if (env->value_ <= env->sustainLevel_)
    {
    	env->value_ = env->sustainLevel_;
    	env->rate_ = 0.0f;
    	env->state_ = SUSTAIN;
    }
    break;

  case RELEASE:
	  env->value_ -= env->releaseRate_;
    if (env->value_ <= 0.0f)
    {
    	env->value_ =  0.0f;
    	env->state_ = DONE;
    }
  }

  env->lastOutput_ = env->value_;
  return env->value_;
}

/*******************************************************   EOF   ***********************************************************/
