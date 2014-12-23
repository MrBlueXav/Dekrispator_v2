/**
 ******************************************************************************
 * @file     phaser.c
 * @author  Xavier Halgand, thanks to Ross Bencina and music-dsp.org guys !
 * @version
 * @date    december 2012
 * @brief

 ******************************************************************************
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#include "phaser.h"

/*---------------------------------------------------------------------*/
#define MAX_RATE		7.f // in Hz
#define MIN_RATE		0.02f // in Hz

/*This defines the phaser stages
that is the number of allpass filters
 */
#define PH_STAGES 6

/*---------------------------------------------------------------------*/

static float 	old[PH_STAGES];
static float 	f_min, f_max;
static float 	swrate;
static float 	wet ;
static float	dmin, dmax; //range
static float	fb; //feedback
static float 	lfoPhase;
static float 	lfoInc;
static float	a1;
static float	zm1;

/*---------------------------------------------------------------------*/
void PhaserInit(void)
{
	f_min = 200.f;
	f_max = 1700.f;
	swrate = 0.1f;
	fb = 0.7f;
	wet = 0.3f;

	dmin = 2 * f_min / SAMPLERATE;
	dmax = 2 * f_max / SAMPLERATE;
	lfoInc = _2PI * swrate / SAMPLERATE;
}
/*---------------------------------------------------------------------*/
void Phaser_Rate_set(uint8_t val)
{
	swrate = (MAX_RATE - MIN_RATE) / MIDI_MAX * val + MIN_RATE;
	lfoInc = _2PI * swrate / SAMPLERATE;
}
/*---------------------------------------------------------------------*/
void Phaser_Feedback_set(uint8_t val)
{
	fb = 0.999f * val / MIDI_MAX;
}
/*---------------------------------------------------------------------*/
void Phaser_Wet_set(uint8_t val)
{
	wet = val / MIDI_MAX;
}
/*---------------------------------------------------------------------*/
void PhaserRate(float rate)
{
	swrate = rate;
	lfoInc = _2PI * swrate / SAMPLERATE;
}
/*---------------------------------------------------------------------*/
void PhaserFeedback(float fdb)
{
	fb = fdb;
}
/*---------------------------------------------------------------------*/
static float allpass(float yin, int ind)
{
	float yout;

	yout = - yin * a1 + old[ind];
	old[ind] = yout * a1 + yin;
	return yout;
}

/*---------------------------------------------------------------------*/
float Phaser_compute(float xin)
{
	float yout;
	int i;
	float d;

	//calculate and update phaser sweep lfo...

	d  = dmin + (dmax - dmin) * ((sinetable[lrintf(ALPHA * lfoPhase)] + 1.f)*0.5f);

	lfoPhase += lfoInc;
	if( lfoPhase >= _2PI ) 	lfoPhase -= _2PI;

	//update filter coeffs
	a1 = (1.f - d) / (1.f + d);

	//calculate output

	yout = allpass(xin + zm1 * fb, 0);

	for(i = 1; i < PH_STAGES; i++)
	{
		yout = allpass(yout, i);
	}
	zm1 = yout;

	yout = (1 - wet) * xin + wet * yout;

	return yout;
}

