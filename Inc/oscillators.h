/**
 ******************************************************************************
 * File Name          	: oscillators.h
 * Author				: Xavier Halgand
 * Date               	:
 * Description        	:
 ******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OSCILLATORS_H
#define __OSCILLATORS_H

/*--------------------- Global Defines ------------------------ */
#define PARTIALS_NUMBER		10 // number of computed harmonics in the additive generator

/* Includes ------------------------------------------------------------------*/
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include "CONSTANTS.h"
#include "math_tools.h"
#include "random.h"
#include "drifter.h"
#include "sinetable.h"
#include "notesTables.h"
#include "drifter.h"
#include "blepvco.h"
/*----------------------------------------------------------------------------*/

enum timbre { MORPH_SAW = 0, SPLIT, ACC_SINE, WT_SINE, ADDITIVE, POWER_SINE, BLEPTRIANGLE, BLEPSQUARE,
	NOISE, CHORD15, CHORD135, CHORD13min5, VOICES3, DRIFTERS, FM2, BLEPSAW, LAST_SOUND };

/*----------------------------------------------------------------------------*/
typedef struct
{
	float_t 	amp;	// should be <= 1 for normal sound output
	float_t		last_amp;
	float_t 	freq;	// Hertz
	float_t 	phase;	// radians
	float_t		phi0;	// radians
	float_t		modInd;	// Modulation Index for FM
	float_t		mul;	// pitch frequency multiplier
	float_t 	out;	// output sample

} Oscillator_t;

/* Exported functions ------------------------------------------------------- */

float_t OpSampleCompute0(Oscillator_t * op); // accurate sine
/*-------------------------------------------------------*/
float_t OpSampleCompute1(Oscillator_t * op); // basic sawtooth^2
/*-------------------------------------------------------*/
float_t OpSampleCompute2(Oscillator_t * op); // basic sawtooth
/*-------------------------------------------------------*/
float_t OpSampleCompute3(Oscillator_t * op); // sin(phi)^5
/*-------------------------------------------------------*/
float_t OpSampleCompute4(Oscillator_t * op); // Complex waveform : +/- |sin(phi)|^alpha(freq), tends to a sine at high freqs
/*-------------------------------------------------------*/
float_t OpSampleCompute5(Oscillator_t * op); // Basic Triangle
/*-------------------------------------------------------*/
float_t MorphingSaw_SampleCompute(Oscillator_t * op); // Morphing sawtooth, tends to a triangle at high freqs
/*-------------------------------------------------------*/
float_t Osc_WT_SINE_SampleCompute(Oscillator_t * op) ;// basic wave table sine
float_t Osc_FM_sine_SampleCompute(Oscillator_t * op, float FMinput); // basic wave table sine with FM
/*-------------------------------------------------------*/
float_t OpSampleCompute7bis(Oscillator_t * op); // basic wave table positive sine : 0 < output < op.amp
/*-------------------------------------------------------*/
float_t BasicSquare_SampleCompute(Oscillator_t * op); // basic square
/*-------------------------------------------------------*/
void 	AdditiveGen_newWaveform(void); //
/*-------------------------------------------------------*/
float_t AdditiveGen_SampleCompute(Oscillator_t * op); // additive sine generator
/*-------------------------------------------------------*/
float_t FM1_sampleCompute(void); // op4 -> op3 -> op2 -> op1 => sound
float_t FM2_sampleCompute(float frq); // (op2 -> op1) + (op4 -> op3) => sound
void 	FM_op_freq_set(Oscillator_t *op, uint8_t val);
void 	FM_op_modInd_set(Oscillator_t *op, uint8_t val);
/*-------------------------------------------------------*/
void 	osc_init(Oscillator_t * op, float_t amp, float_t freq);
/*-------------------------------------------------------*/
void 	OpSetFreq(Oscillator_t * op, float_t f);
/*-------------------------------------------------------*/
void	Drifter_centralFreq_set(uint8_t val);
float	Lin2Exp(uint8_t val, float min, float max); // input val in 0 ... 127
/*-------------------------------------------------------*/
float 	waveCompute(uint8_t sound, float f0);

/****************************************************************************************************************************/
#endif /* __OSCILLATORS_H */
