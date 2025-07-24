/**
 ******************************************************************************
 * File Name          : chorusFD.c
 * Author			  : Xavier Halgand (thanks to Gabriel Rivas)
 * Date               :
 * Description        : stereo chorus/flanger
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
#include "chorusFD.h"


/* Private define ------------------------------------------------------------*/
#define MARGIN			6 // minimal delay (in samples)


/************************************************************************************************************
 *                       chorus/flanger diagram (one channel) :
 *
 *                    ---------[mix >----------------------------
 *                    |                                         |
 *                    |                                         |
 *                    |x1                                       v
 *     xin ------>[+]----->[z^-M]--[interp.]----[fw >--------->[+]-----> yout
 *                 ^         delay line      |
 *                 |                         |
 *                 --< fb]<-------------------
 *
 ************************************************************************************************************/


static Lfo_t			lfoL _CCM_ , lfoR _CCM_ ; // 2 independant LFOs
static monochorus_t		delR  _CCM_ , delL  _CCM_ ; // 2 fractional delay lines
float rateCoeff;

/*-------------------------------------------------------------------------------------------*/
float Lfo_SampleCompute(Lfo_t * op) // ! returns a positive value between 0 and op.amp !
{
	float z;

	op->phase += _2PI * Ts * op->freq; // increment phase
	while (op->phase < 0) // keep phase in [0, 2pi]
		op->phase += _2PI;
	while (op->phase >= _2PI)
		op->phase -= _2PI;

	z = sinetable[lrintf(ALPHA * (op->phase))];
	op->out = op->amp * (z + 1); // returns a positive value between 0 and op.amp

	return op->out;
}

/*---------------------------------------------------------------------------------------------*/
void ChorusDelay_init(monochorus_t *del, float delay, float dfb, float dfw, float dmix)
{
	Delay_set_fb(del, dfb);
	Delay_set_fw(del, dfw);
	Delay_set_mix(del, dmix);
	Delay_set_delay(del, delay);
	del->in_idx = DEPTH - 1;// Place the input pointer at the end of the buffer
	del->mode = 1;
}

/********************************************* CHORUS interface ************************************************************/

void Chorus_init(void)
{
	ChorusDelay_init(&delL, LEFT_DELAY, FEEDBACK, FORWARD, MIX);
	ChorusDelay_init(&delR, RIGHT_DELAY, FEEDBACK, FORWARD, MIX);
	lfoL.amp = LEFT_SWEEP;
	lfoR.amp = RIGHT_SWEEP;
	lfoL.freq = LEFT_RATE ;
	lfoR.freq = RIGHT_RATE ;
	rateCoeff = 1;
	lfoL.phase = _PI/2; // initial phases for quadrature
	lfoR.phase = 0;

	for (int var = 0; var < DEPTH; ++var) {
		delR.dline[var] = 0;
		delL.dline[var] = 0;
	}
}
/*---------------------------------------------------------------------------------------------*/
void Chorus_reset(uint8_t val)
{
	if (val == MIDI_MAXi)
		Chorus_init();
}
/*-------------------------------------------------------------------------------------------*/
void inc_chorusRate(void)
{
	lfoL.freq *= 1.05f;
	lfoR.freq *= 1.05f;
}
/*-------------------------------------------------------------------------------------------*/
void dec_chorusRate(void)
{
	lfoL.freq *= .95f;
	lfoR.freq *= .95f;
}
/*---------------------------------------------------------------------------------------------*/
void ChorusRate_set(uint8_t val)
{
	float rate;
	rate = MAX_RATE / MIDI_MAX * val + MIN_RATE;
	lfoL.freq = rate;
	//lfoR.freq = 0.98f * rate;
	lfoR.freq = rateCoeff * rate;
}
/*---------------------------------------------------------------------------------------------*/
void ChorusSecondRate_set(uint8_t val)
{
	rateCoeff = 0.9f / MIDI_MAX * val + 0.1f; // from 10 % to 100 % of lfoL rate
	lfoR.freq = rateCoeff * lfoL.freq;
}
/*-------------------------------------------------------------------------------------------*/
void inc_chorusDelay(void)
{
	float d;

	d = delL.baseDelay * 1.1f;
	if (d < DEPTH)
	{
		delL.baseDelay = d;
	}

	d = delR.baseDelay * 1.1f;
	if (d < DEPTH)
	{
		delR.baseDelay = d;
	}
}
/*-------------------------------------------------------------------------------------------*/
void dec_chorusDelay(void)
{
	delL.baseDelay *= .9f;
	delR.baseDelay *= .9f;
}
/*---------------------------------------------------------------------------------------------*/
void ChorusDelay_set(uint8_t val)
{
	float d;
	d = 0.5f * DEPTH / MIDI_MAX * val ;
	delL.baseDelay = d;
	delR.baseDelay = d;
}
/*-------------------------------------------------------------------------------------------*/
void inc_chorusFeedback(void)
{
	/* increase feedback delay */

	delL.fb *= 1.02f ;//
	delR.fb *= 1.02f ;//
}
/*-------------------------------------------------------------------------------------------*/
void dec_chorusFeedback(void)
{
	/* decrease feedback delay */

	delL.fb *= 0.95f ;//
	delR.fb *= 0.95f ;//
}
/*---------------------------------------------------------------------------------------------*/
void ChorusFeedback_set(uint8_t val)
{
	float_t fb;
	fb = 0.95f * val / MIDI_MAX;
	delL.fb = fb;
	delR.fb = fb;
}
/*-------------------------------------------------------------------------------------------*/
void inc_chorusSweep(void)
{
	lfoL.amp *= 1.05f ;//
	lfoR.amp *= 1.05f ;//
}
/*-------------------------------------------------------------------------------------------*/
void dec_chorusSweep(void)
{
	lfoL.amp *= .95f ;//
	lfoR.amp *= .95f ;//
}
/*---------------------------------------------------------------------------------------------*/
void ChorusSweep_set(uint8_t val)
{
	float sw;
	sw = 0.1f * (DEPTH - MARGIN)/MIDI_MAX * val;
	lfoL.amp = sw;
	lfoR.amp = sw;
}
/*-------------------------------------------------------------------------------------------*/
void ChorusMode_toggle(void)
{
	delL.mode *= -1 ;//
	delR.mode *= -1 ;//
}
/*---------------------------------------------------------------------------------------------*/
void ChorusMode_switch(uint8_t val)
{
	switch (val)
		{
		case 127 : 	delR.mode = delL.mode = -1 ; break;
		case 0 : 	delR.mode = delL.mode = 1 ; break;
		}
}
/*-------------------------------------------------------------------------------------------*/
void ChorusFDBsign_change(void)
{
	delL.fb *= -1.f ;//
	delR.fb *= -1.f ;//
}
/*---------------------------------------------------------------------------------------------*/
void ChorusFDBsign_switch(uint8_t val)
{
	switch (val)
		{
		case 127 : 	delR.fb = fabsf(delR.fb); delL.fb = fabsf(delL.fb); break; // positive feedback;
		case 0 : 	delR.fb = - fabsf(delR.fb); delL.fb = - fabsf(delL.fb); break; // negative feedback;
		}
}
/*-------------------------------------------------------------------------------------------*/
void Delay_set_delay(monochorus_t *del, float delay)
{
	del->baseDelay = delay;
}
/*-------------------------------------------------------------------------------------------*/
void Delay_set_fb(monochorus_t *del, float val)
{
	del->fb = val;
}
/*-------------------------------------------------------------------------------------------*/
void Delay_set_fw(monochorus_t *del, float val)
{
	del->fw = val;
}
/*-------------------------------------------------------------------------------------------*/
void Delay_set_mix(monochorus_t *del, float val)
{
	del->mix = val;
}
/*-------------------------------------------------------------------------------------------*/
float Delay_get_fb(monochorus_t *del )
{
	return del->fb;
}
/*-------------------------------------------------------------------------------------------*/
float Delay_get_fw(monochorus_t *del )
{
	return del->fw;
}
/*-------------------------------------------------------------------------------------------*/
float Delay_get_mix(monochorus_t *del )
{
	return del->mix;
}
/*-------------------------------------------------------------------------------------------*/
void delay_write (monochorus_t *del, float xin)
{
	del->dline[del->in_idx] = xin;

	(del->in_idx)++;
	if (del->in_idx >= DEPTH)
		del->in_idx = 0;
}
/*-------------------------------------------------------------------------------------------*/
float delay_read (monochorus_t *del, float delay) // "delay" is a floating point number of samples
{
	float d;		// true requested delay (floating point number of samples)
	float f;		// fractional part of delay
	int32_t i;		// integer part of delay
	float y_n;		// y(n)
	float y_n_1;	// y(n-1)
	float y_n_2;	// y(n-2)
	float y_n_3;	// y(n-3)
	int32_t idx;

	d = delay;
	if (d < MARGIN) d = MARGIN; // MARGIN is the minimum allowed delay
	if (d > DEPTH-MARGIN) d = DEPTH-MARGIN;

	i = (int32_t)floorf(d);
	f = d - i;

	idx = del->in_idx - i;
	if (idx < 0) idx += DEPTH;
	y_n = del->dline[idx]; 		// y(n)

	idx--;
	if (idx < 0) idx += DEPTH;
	y_n_1 = del->dline[idx];	// y(n-1)

	idx--;
	if (idx < 0) idx += DEPTH;
	y_n_2 = del->dline[idx];	// y(n-2)

	idx--;
	if (idx < 0) idx += DEPTH;
	y_n_3 = del->dline[idx];	// y(n-3)

	//return (y_n_1 - y_n) * f + y_n ; // linear interpolation

	//return (.5f)*(f-1)*(f-2)*y_n - f*(f-2)*y_n_1 + (.5f)*f*(f-1)*y_n_2 ; // 2nd order Lagrange interpolation

	//return .5f*(f-1)*((f-2)*y_n + f*y_n_2) - f*(f-2)*y_n_1 ;	// 2nd order Lagrange interpolation (faster)

	/* 3rd order Lagrange interpolation :  */
	return (f-2)*(f-3)*(-0.16666666666f *(f-1)*y_n + 0.5f * f * y_n_1) + f*(f-1)*(-0.5f * (f-3)*y_n_2 + 0.166666666666f * (f-2)*y_n_3);

}
/*---------------------------------------------------------------------------------------------*/

float mono_chorus_compute(monochorus_t *del, Lfo_t *lfo, float xin)
{
	float yout;
	float x1;
	float x2;

	x2 = delay_read (del, del->baseDelay + Lfo_SampleCompute(lfo) + MARGIN);

	if (del->mode == 1)
		x1 = xin + del->fb * x2; // variable delay feedback signal or ...
	else
		x1 = xin + del->fb * delay_read (del, del->baseDelay + MARGIN); // fixed delay feedback signal

	x1 = (x1 > 1.0f) ? 1.0f : x1 ; //clip too loud samples
	x1 = (x1 < -1.0f) ? -1.0f : x1 ;

	yout = del->mix * x1 + del->fw * x2;
	//yout = del->mix * xin + del->fw * x2; // not good sounding...
	delay_write(del, x1);

	return yout;
}

/*--------------------This is the main stereo chorus function : ----------------------------*/

void stereoChorus_compute (float * left_out, float * right_out, float in)
{
	*left_out = mono_chorus_compute(&delL, &lfoL, in);
	*right_out = mono_chorus_compute(&delR, &lfoR, in);
}


/*-----------------------------------------------------------------------END--------------------------------------------*/

