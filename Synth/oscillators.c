/**
 ******************************************************************************
 * File Name          : oscillators.c
 * Author			  : Xavier Halgand
 * Date               :
 * Description        :
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

#include "oscillators.h"

/*------------------------------------------------------------------------*/
extern Drifter_t 	d1 , d2 , d3 ;
extern VCO_blepsaw_t		mbSawOsc;
extern VCO_bleprect_t		mbRectOsc;
extern VCO_bleptri_t		mbTriOsc;

/*------------------------------------------------------------------------*/
Oscillator_t 		op1 _CCM_;
Oscillator_t 		op2 _CCM_;
Oscillator_t 		op3 _CCM_;
Oscillator_t 		op4 _CCM_;

Oscillator_t 		vibr_lfo _CCM_;

Oscillator_t 		filt_lfo _CCM_;
Oscillator_t 		filt2_lfo _CCM_;

Oscillator_t 		amp_lfo _CCM_;

static float_t			a[PARTIALS_NUMBER + 1] _CCM_ ; // additive generator amplitudes
static float_t			ph[PARTIALS_NUMBER + 1] _CCM_ ; // additive generator phases

static float_t			centralFreq = 3000;

/*===============================================================================================================*/

void
osc_init(Oscillator_t * op, float_t amp, float_t freq)
{
	op->amp = amp;
	op->last_amp = amp;
	op->freq = freq;
	op->phase = 0;
	op->out = 0;
	op->modInd = 0;
	op->mul = 1;
}
/*-------------------------------------------------------*/

void
OpSetFreq(Oscillator_t * op, float_t f)
{
	op->freq = f;
}

/*---------------------------------------------------------------*/
void	Drifter_centralFreq_set(uint8_t val)
{
	centralFreq = Lin2Exp(val, 1, 6000);
}
/*---------------------------------------------------------------*/
float_t Drifters_sampleCompute(void) // 3 drifting sawtooths with "fixed" main pitch in centralFreq variable
{
	float y;

	OpSetFreq(&op1, 25 + centralFreq * (1 + drifter_nextSample(&d1)));
	OpSetFreq(&op2, 25 + centralFreq * (1 + drifter_nextSample(&d2)));
	OpSetFreq(&op3, 25 + centralFreq * (1 + drifter_nextSample(&d3)));

	//y = 0.33f * (Osc_WT_SINE_SampleCompute(&op1) + Osc_WT_SINE_SampleCompute(&op2) + Osc_WT_SINE_SampleCompute(&op3));
	y = 0.33f * (MorphingSaw_SampleCompute(&op1) + MorphingSaw_SampleCompute(&op2) + MorphingSaw_SampleCompute(&op3));

	return y;
}


/*---------------------------------------------------------------*/
void FM_op_freq_set(Oscillator_t *op, uint8_t val)
{
	op->freq = Lin2Exp(val, 0.5f, 8000.f);
}
/*-------------------------------------------------------*/
void FM_op_modInd_set(Oscillator_t *op, uint8_t val)
{
	op->modInd = (1.4f * val / MIDI_MAX) * (1.4f * val / MIDI_MAX);
}
/*-----------------------------------------------------------------------------------------------*/
float_t FM1_sampleCompute(void) // op4 -> op3 -> op2 -> op1 => sound
{
	Osc_WT_SINE_SampleCompute(&op4); // The result is in op4.out !
	op3.phase += op3.modInd * op4.out;
	Osc_WT_SINE_SampleCompute(&op3);
	op2.phase += op2.modInd * op3.out;
	Osc_WT_SINE_SampleCompute(&op2);
	op1.phase += op1.modInd * op2.out;
	Osc_WT_SINE_SampleCompute(&op1);

	return op1.out;
}
/*-----------------------------------------------------------------------------------------------*/
float_t FM2_sampleCompute(float frq) //  (op2 -> op1) + (op4 -> op3) => sound
{
	float in;
	op1.freq = frq;
	op2.freq = op2.mul * frq;
	op3.freq = op3.mul * frq;
	op4.freq = op4.mul * frq;
	in = Osc_FM_sine_SampleCompute(&op2, 0);
	Osc_FM_sine_SampleCompute(&op1, in);
	in = Osc_FM_sine_SampleCompute(&op4, 0);
	Osc_FM_sine_SampleCompute(&op3, in);

	return  0.5f * (op1.out + op3.out);
}
/*----------------------------------------------------------------------------------------------*/
float_t OpSampleCompute0(Oscillator_t * op) // accurate sine
{
	float_t z;


	while (op->phase >= _2PI) // keep phase in [0, 2pi]
		op->phase -= _2PI;

	z = sinf(op->phase);
	op->out = op->amp*z;

	op->phase += _2PI * Ts * op->freq; // increment phase
	return op->out;
}
/*-------------------------------------------------------*/
float_t Osc_WT_SINE_SampleCompute(Oscillator_t * op) // basic wave table sine
{
	while (op->phase < 0) // keep phase in [0, 2pi]
		op->phase += _2PI;
	while (op->phase >= _2PI)
		op->phase -= _2PI;

	op->out = op->amp * sinetable[lrintf(ALPHA * (op->phase))];
	op->phase += _2PI * Ts * op->freq; // increment phase

	return op->out;
}
/*-------------------------------------------------------*/
float_t Osc_FM_sine_SampleCompute(Oscillator_t * op, float FMinput) // basic wave table sine with FM
{

	op->phase += _2PI * Ts * op->freq + op->modInd * FMinput; // increment phase
	while (op->phase < 0) // keep phase in [0, 2pi]
		op->phase += _2PI;
	while (op->phase >= _2PI)
		op->phase -= _2PI;
	op->out = op->amp * sinetable[lrintf(ALPHA * (op->phase))];
	return op->out;
}
/*-------------------------------------------------------*/
float_t OpSampleCompute7bis(Oscillator_t * op) // basic wave table positive sine : 0 < output < op.amp
{
	while (op->phase < 0) // keep phase in [0, 2pi]
		op->phase += _2PI;
	while (op->phase >= _2PI)
		op->phase -= _2PI;

	op->out = op->amp * 0.5f * (1.f + sinetable[lrintf(ALPHA * (op->phase))]);
	op->phase += _2PI * Ts * op->freq; // increment phase

	return op->out;
}
/*-------------------------------------------------------*/
float_t OpSampleCompute1(Oscillator_t * op) // basic sawtooth^2
{
	while (op->phase < 0) // keep phase in [0, 2pi]
		op->phase += _2PI;
	while (op->phase >= _2PI)
		op->phase -= _2PI;

	if (op->phase < _PI) op->out = 0.5f * op->amp * (op->phase / _PI)*(op->phase / _PI);
	else op->out = - .5f*(op->amp * (op->phase / _PI - 2)*(op->phase / _PI - 2));

	op->phase += _2PI * Ts * op->freq; // increment phase
	return op->out;
}
/*-------------------------------------------------------*/
float_t OpSampleCompute2(Oscillator_t * op) // basic sawtooth
{
	while (op->phase < 0) // keep phase in [0, 2pi]
		op->phase += _2PI;
	while (op->phase >= _2PI)
		op->phase -= _2PI;

	if (op->phase < _PI) op->out = 0.5f*op->amp * (op->phase / _PI);
	else op->out =  .5f*op->amp * (op->phase / _PI - 2);

	op->phase += _2PI * Ts * op->freq; // increment phase
	return op->out;
}
/*-------------------------------------------------------*/
float_t OpSampleCompute3(Oscillator_t * op) // sin(phi)^5
{
	float_t z;

	while (op->phase < 0) // keep phase in [0, 2pi]
		op->phase += _2PI;
	while (op->phase >= _2PI)
		op->phase -= _2PI;

	z = sinf(op->phase);
	op->out = op->amp*z*z*z*z*z;

	op->phase += _2PI * Ts * op->freq; // increment phase
	return op->out;
}
/*-------------------------------------------------------*/
float_t OpSampleCompute4(Oscillator_t * op) // Complex waveform : +/- |sin(phi)|^alpha(freq), tends to a sine at high freqs
{
	float_t z, x, alpha;

	while (op->phase < 0) // keep phase in [0, 2pi]
		op->phase += _2PI;
	while (op->phase >= _2PI)
		op->phase -= _2PI;

	x = op->freq;
	//alpha = 3.f;
	//http://www.math.ucla.edu/~ronmiech/Interpolation/HTMDOCS/Introduction/Interpolation_Applet.htm  :
	alpha = 81.096f + x*(-.037f + .582E-5f*x -.311E-9f*x*x) ; //alpha varies from 80 to 1 with freq from 30Hz to 8000Hz
	//alpha = 60.695f -.023f * x + .31E-5f * x*x -.141E-9f * x*x*x ;
	//alpha = (50.f-1)/(30.f-8000)*(x - 8000) + 1 ;
	//z = powf(fabsf(sinf(op->phase )), alpha) ;

	z = powf(fabsf(sinetable[lrintf(ALPHA * (op->phase))]), alpha) ;

	if (op->phase < _PI) op->out = op->amp * z;
	else op->out = - op->amp * z;

	op->phase += _2PI * Ts * op->freq; // increment phase

	return op->out;
}
/*-------------------------------------------------------*/
float_t OpSampleCompute5(Oscillator_t * op) // Naive Triangle
{
	while (op->phase < 0) // keep phase in [0, 2pi]
		op->phase += _2PI;
	while (op->phase >= _2PI)
		op->phase -= _2PI;

	if (op->phase < _PI) op->out = op->amp * (-2/_PI * op->phase + 1);
	else op->out =  op->amp * (2/_PI * op->phase - 3);

	op->phase += _2PI * Ts * op->freq; // increment phase
	return op->out;
}
/*-------------------------------------------------------*/
float_t MorphingSaw_SampleCompute(Oscillator_t * op) // Morphing sawtooth, tends to a triangle at high freqs
{
	while (op->phase < 0) // keep phase in [0, 2pi]
		op->phase += _2PI;
	while (op->phase >= _2PI)
		op->phase -= _2PI;

	if (op->freq < 8000) op->phi0 = _PI/8000*(op->freq); else op->phi0 = _PI;
	if (op->phi0 <= .0001f) op->phi0 = .0001f;
	if (op->phase < op->phi0) op->out = op->amp * (-2/op->phi0 * op->phase + 1);
	else op->out =  op->amp * (2 * op->phase - _2PI - op->phi0)/(_2PI - op->phi0);

	op->phase += _2PI * Ts * op->freq; // increment phase
	return op->out;
}
/*-------------------------------------------------------*/
float_t BasicSquare_SampleCompute(Oscillator_t * op) // naive square
{

	while (op->phase < 0) // keep phase in [0, 2pi]
		op->phase += _2PI;
	while (op->phase >= _2PI)
		op->phase -= _2PI;

	if (op->phase < _PI) op->out = op->amp ;
	else op->out = - op->amp ;

	op->phase += _2PI * Ts * op->freq; // increment phase
	return op->out;
}
/*-------------------------------------------------------*/
void AdditiveGen_newWaveform(void) //
{
	uint8_t k;

	a[0] = a[1] = 1;
	ph[0] = ph[1] = 0;

	for ( k= 2; k <= PARTIALS_NUMBER ; k++)
	{
		a[k] = frand_a_b(0.001f , 0.98f);
		a[0] += a[k];
		ph[k] = 0;
	}
	a[0] = 1.f / a[0];
}
/*-------------------------------------------------------*/
float_t AdditiveGen_SampleCompute(Oscillator_t * op) // additive sine generator
{
	uint8_t k = 1;
	float_t y = 0;

	while ((k <= PARTIALS_NUMBER ) && (k * op->freq < SAMPLERATE/2.f))
	{
		//while (ph[k] < 0) // keep phase in [0, 2pi]
		//	ph[k] += _2PI;
		while (ph[k] >= _2PI)
			ph[k] -= _2PI;
		y += a[k] * sinetable[(uint16_t)(ALPHA * (ph[k]))];
		ph[k] += _2PI * Ts * k * op->freq; // increment phase
		k++;
	}
	y = a[0] * y;

	op->out = op->amp * y;

	return op->out;
}

/*-------------------------------------------------------------------------------------------------------------------*/

float waveCompute(uint8_t sound, float frq)
{
	float y;

	OpSetFreq(&op1, frq);


	/* choose waveform generator */
	switch (sound)
	{
	case MORPH_SAW : 	y = 0.8f * MorphingSaw_SampleCompute(&op1); 		break ;

	case SPLIT :  	{
		if (frq < 200) y =  OpSampleCompute1(&op1);
		else if (frq < 600) y = OpSampleCompute2(&op1);
		else y = OpSampleCompute5(&op1);
	} 	break;

	case ACC_SINE : 		y = 0.8 * OpSampleCompute0(&op1); 		break;

	case POWER_SINE : 		y = OpSampleCompute3(&op1);				break;

	case BLEPTRIANGLE :	 	mbTriOsc.freq = frq;
	y = VCO_bleptri_SampleCompute(&mbTriOsc); break;

	case BLEPSQUARE : 		mbRectOsc.freq = frq;
	y = VCO_bleprect_SampleCompute(&mbRectOsc);		break;

	case WT_SINE : 			y = 0.8f * Osc_WT_SINE_SampleCompute(&op1);		break;

	case ADDITIVE : 		y = AdditiveGen_SampleCompute(&op1);	break;

	case NOISE : 			y = op1.amp * frand_a_b(-.8f , .8f);	break; // noise !

	case CHORD15 : 	{	// fundamental + fifth : 1 5
		OpSetFreq(&op2, frq * 1.50f);
		y =  0.5f *(MorphingSaw_SampleCompute(&op1) + MorphingSaw_SampleCompute(&op2));
	} break;

	case CHORD135 :	{	// major chord : 1 3maj 5
		OpSetFreq(&op2, frq * 1.26f);
		OpSetFreq(&op3, frq * 1.5f);
		y = 0.33f *(MorphingSaw_SampleCompute(&op1) + MorphingSaw_SampleCompute(&op2) + MorphingSaw_SampleCompute(&op3));
	} break;

	case CHORD13min5 :	{	// minor chord : 1 3min 5
		OpSetFreq(&op2, frq * 1.1892f);
		OpSetFreq(&op3, frq * 1.5f);
		y = 0.33f *(MorphingSaw_SampleCompute(&op1) + MorphingSaw_SampleCompute(&op2) + MorphingSaw_SampleCompute(&op3));
	} break;

	case VOICES3 :	{ // 3 slightly detuned oscillators with drifters

		OpSetFreq(&op2, frq * (1 + d1_drifter_nextSample()));
		OpSetFreq(&op3, frq * (1 + d2_drifter_nextSample()));
		y = 0.33f *(MorphingSaw_SampleCompute(&op1) + MorphingSaw_SampleCompute(&op2) + MorphingSaw_SampleCompute(&op3));
	} break;

	case DRIFTERS : 	y = Drifters_sampleCompute(); break;

	case FM2 : 			y = FM2_sampleCompute(frq); break;

	case BLEPSAW :		{
		mbSawOsc.freq = frq;
		y = VCO_blepsaw_SampleCompute(&mbSawOsc);
	}	break;

	default :
		y = 0;	break ;

	}

	return y;
}

/****************************************EOF***************************************************/
