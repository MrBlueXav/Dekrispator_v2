/**
 ******************************************************************************
 * File Name          	: blepvco.c
 * Author				: Xavier Halgand + Sean Bolton
 * Date               	:
 * Description        	:
 ******************************************************************************
 */

/* blepvco - minBLEP-based, hard-sync-capable LADSPA VCOs.
 *
 * Copyright (C) 2004-2005 Sean Bolton.
 *
 * Much of the LADSPA framework used here comes from VCO-plugins
 * 0.3.0, copyright (c) 2003-2004 Fons Adriaensen.
 *
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

#define _BSD_SOURCE    1
#define _SVID_SOURCE   1
#define _ISOC99_SOURCE 1

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "minblep_tables.h"
#include "blepvco.h"

/**======================================================================================================**/

VCO_blepsaw_t	mbSawOsc _CCM_;
VCO_bleprect_t	mbRectOsc _CCM_;
VCO_bleptri_t	mbTriOsc _CCM_;

/**======================================================================================================**/


void place_step_dd(float *buffer, int index, float phase, float w, float scale)
{
	float r;
	int i;

	r = MINBLEP_PHASES * phase / w;
	i = lrintf(r - 0.5f);
	r -= (float)i;
	i &= MINBLEP_PHASE_MASK;  /* extreme modulation can cause i to be out-of-range */
	/* this would be better than the above, but more expensive:
	 *  while (i < 0) {
	 *    i += MINBLEP_PHASES;
	 *    index++;
	 *  }
	 */

	while (i < MINBLEP_PHASES * STEP_DD_PULSE_LENGTH) {
		buffer[index] += scale * (step_dd_table[i].value + r * step_dd_table[i].delta);
		i += MINBLEP_PHASES;
		index++;
	}
}
//----------------------------------------------------------------------------------------------------------

void place_slope_dd(float *buffer, int index, float phase, float w, float slope_delta)
{
	float r;
	int i;

	r = MINBLEP_PHASES * phase / w;
	i = lrintf(r - 0.5f);
	r -= (float)i;
	i &= MINBLEP_PHASE_MASK;  /* extreme modulation can cause i to be out-of-range */

	slope_delta *= w;

	while (i < MINBLEP_PHASES * SLOPE_DD_PULSE_LENGTH) {
		buffer[index] += slope_delta * (slope_dd_table[i] + r * (slope_dd_table[i + 1] - slope_dd_table[i]));
		i += MINBLEP_PHASES;
		index++;
	}
}
//----------------------------------------------------------------------------------------------------------

/* ==== hard-sync-capable sawtooth oscillator ==== */

void VCO_blepsaw_Init(VCO_blepsaw_t *vco)
{
	vco->_init = true;
	vco->amp = 1.0f;
	vco->freq = 440.f;
	vco->syncin = 0.0f;
	vco->_z = 0.0f;
	vco->_j = 0;
	memset (vco->_f, 0, (FILLEN + STEP_DD_PULSE_LENGTH) * sizeof (float));
}

//----------------------------------------------------------------------------------------------------------

float VCO_blepsaw_SampleCompute(VCO_blepsaw_t *vco)
{
	int    j;
	float  freq, syncin;
	float  a, p, t, w, dw, z;
	syncin  = vco->syncin;
	freq = vco->freq;

	p = vco->_p;  /* phase [0, 1) */
	w = vco->_w;  /* phase increment */
	z = vco->_z;  /* low pass filter state */
	j = vco->_j;  /* index into buffer _f */

	if (vco->_init) {
		p = 0.5f;
		w = freq / SAMPLERATE;
		if (w < 1e-5) w = 1e-5;
		if (w > 0.5) w = 0.5;
		/* if we valued alias-free startup over low startup time, we could do:
		 *   p -= w;
		 *   place_slope_dd(_f, j, 0.0f, w, -1.0f); */
		vco->_init = false;
	}

	//a = 0.2 + 0.8 * vco->_port [FILT];
	a = 0.5f; // when a = 1, LPfilter is disabled

	t = freq / SAMPLERATE;
	if (t < 1e-5) t = 1e-5;
	if (t > 0.5) t = 0.5;
	dw = (t - w); // n= 1
	w += dw;
	p += w;

	if (syncin >= 1e-20f) {  /* sync to master */

		float eof_offset = (syncin - 1e-20f) * w;
		float p_at_reset = p - eof_offset;
		p = eof_offset;

		/* place any DD that may have occurred in subsample before reset */
		if (p_at_reset >= 1.0f) {
			p_at_reset -= 1.0f;
			place_step_dd(vco->_f, j, p_at_reset + eof_offset, w, 1.0f);
		}

		/* now place reset DD */
		place_step_dd(vco->_f, j, p, w, p_at_reset);

		vco->syncout = syncin;  /* best we can do is pass on upstream sync */

	} else if (p >= 1.0f) {  /* normal phase reset */

		p -= 1.0f;
		vco->syncout = p / w + 1e-20f;
		place_step_dd(vco->_f, j, p, w, 1.0f);

	} else {

		vco->syncout = 0.0f;
	}
	vco->_f[j + DD_SAMPLE_DELAY] += 0.5f - p;

	z += a * (vco->_f[j] - z); // LP filtering
	vco->out = vco->amp * z;

	if (++j == FILLEN)
	{
		j = 0;
		memcpy (vco->_f, vco->_f + FILLEN, STEP_DD_PULSE_LENGTH * sizeof (float));
		memset (vco->_f + STEP_DD_PULSE_LENGTH, 0,  FILLEN * sizeof (float));
	}

	vco->_p = p;
	vco->_w = w;
	vco->_z = z;
	vco->_j = j;

	return vco->out;
}

//----------------------------------------------------------------------------------------------------------
/* ==== variable-width, hard-sync-capable rectangular oscillator ==== */

void VCO_bleprect_Init(VCO_bleprect_t *vco)
{
	vco->_init = true;
	vco->amp = 1.0f;
	vco->freq = 440.f;
	vco->syncin = 0.0f;
	vco->waveform = 0.0f;
	vco->_z = 0.0f;
	vco->_j = 0;
	memset (vco->_f, 0, (FILLEN + STEP_DD_PULSE_LENGTH) * sizeof (float));
}
////----------------------------------------------------------------------------------------------------------

float VCO_bleprect_SampleCompute(VCO_bleprect_t *vco)
{
	int    j, k;
	float  freq, syncin;
	float  a, b, db, p, t, w, dw, x, z;

	syncin  = vco->syncin;
	freq = vco->freq;
	p = vco->_p;  /* phase [0, 1) */
	w = vco->_w;  /* phase increment */
	b = vco->_b;  /* duty cycle (0, 1) */
	x = vco->_x;  /* temporary output variable */
	z = vco->_z;  /* low pass filter state */
	j = vco->_j;  /* index into buffer _f */
	k = vco->_k;  /* output state, 0 = high (0.5f), 1 = low (-0.5f) */
	//
	if (vco->_init) {
		p = 0.0f;

		w = freq / SAMPLERATE;
		if (w < 1e-5) w = 1e-5;
		if (w > 0.5) w = 0.5;
		b = 0.5 * (1.0 + vco->waveform );
		if (b < w) b = w;
		if (b > 1.0f - w) b = 1.0f - w;
		/* for variable-width rectangular wave, we could do DC compensation with:
		 *     x = 1.0f - b;
		 * but that doesn't work well with highly modulated hard sync.  Instead,
		 * we keep things in the range [-0.5f, 0.5f]. */
		x = 0.5f;
		/* if we valued alias-free startup over low startup time, we could do:
		 *   p -= w;
		 *   place_step_dd(_f, j, 0.0f, w, 0.5f); */
		k = 0;
		vco->_init = false;
	}
	//
	//	a = 0.2 + 0.8 * vco->_port [FILT];
	a = 0.5f; // when a = 1, LPfilter is disabled

	t = freq / SAMPLERATE;
	if (t < 1e-5) t = 1e-5;
	if (t > 0.5) t = 0.5;
	dw = (t - w) ;
	t = 0.5 * (1.0 + vco->waveform );
	if (t < w) t = w;
	if (t > 1.0f - w) t = 1.0f - w;
	db = (t - b) ;

	w += dw;
	b += db;
	p += w;

	if (syncin >= 1e-20f) {  /* sync to master */
		//
		float eof_offset = (syncin - 1e-20f) * w;
		float p_at_reset = p - eof_offset;
		p = eof_offset;

		/* place any DDs that may have occurred in subsample before reset */
		if (!k) {
			if (p_at_reset >= b) {
				place_step_dd(vco->_f, j, p_at_reset - b + eof_offset, w, -1.0f);
				k = 1;
				x = -0.5f;
			}
			if (p_at_reset >= 1.0f) {
				p_at_reset -= 1.0f;
				place_step_dd(vco->_f, j, p_at_reset + eof_offset, w, 1.0f);
				k = 0;
				x = 0.5f;
			}
		} else {
			if (p_at_reset >= 1.0f) {
				p_at_reset -= 1.0f;
				place_step_dd(vco->_f, j, p_at_reset + eof_offset, w, 1.0f);
				k = 0;
				x = 0.5f;
			}
			if (!k && p_at_reset >= b) {
				place_step_dd(vco->_f, j, p_at_reset - b + eof_offset, w, -1.0f);
				k = 1;
				x = -0.5f;
			}
		}

		/* now place reset DD */
		if (k) {
			place_step_dd(vco->_f, j, p, w, 1.0f);
			k = 0;
			x = 0.5f;
		}
		if (p >= b) {
			place_step_dd(vco->_f, j, p - b, w, -1.0f);
			k = 1;
			x = -0.5f;
		}

		vco->syncout = syncin;  /* best we can do is pass on upstream sync */

	} else if (!k) {  /* normal operation, signal currently high */

		if (p >= b) {
			place_step_dd(vco->_f, j, p - b, w, -1.0f);
			k = 1;
			x = -0.5f;
		}
		if (p >= 1.0f) {
			p -= 1.0f;
			vco->syncout = p / w + 1e-20f;
			place_step_dd(vco->_f, j, p, w, 1.0f);
			k = 0;
			x = 0.5f;
		} else {
			vco->syncout = 0.0f;
		}

	} else {  /* normal operation, signal currently low */

		if (p >= 1.0f) {
			p -= 1.0f;
			vco->syncout = p / w + 1e-20f;
			place_step_dd(vco->_f, j, p, w, 1.0f);
			k = 0;
			x = 0.5f;
		} else {
			vco->syncout = 0.0f;
		}
		if (!k && p >= b) {
			place_step_dd(vco->_f, j, p - b, w, -1.0f);
			k = 1;
			x = -0.5f;
		}
	}
	vco->_f[j + DD_SAMPLE_DELAY] += x;

	z += a * (vco->_f[j] - z);
	vco->out = vco->amp * z;

	if (++j == FILLEN)
	{
		j = 0;
		memcpy (vco->_f, vco->_f + FILLEN, STEP_DD_PULSE_LENGTH * sizeof (float));
		memset (vco->_f + STEP_DD_PULSE_LENGTH, 0,  FILLEN * sizeof (float));
	}

	vco->_p = p;
	vco->_w = w;
	vco->_b = b;
	vco->_x = x;
	vco->_z = z;
	vco->_j = j;
	vco->_k = k;

	return vco->out;

}

//----------------------------------------------------------------------------------------------------------

///* ==== variable-slope, hard-sync-capable triangle oscillator ==== */

void VCO_bleptri_Init(VCO_bleptri_t *vco)
{
	vco->amp = 1.0f;
	vco->freq = 440.f;
	vco->syncin = 0.0f;
	vco->waveform = 0.0f;
	vco->_init = true;
	vco->_z = 0.0f;
	vco->_j = 0;
	memset (vco->_f, 0, (FILLEN + STEP_DD_PULSE_LENGTH) * sizeof (float));
}
////----------------------------------------------------------------------------------------------------------

float VCO_bleptri_SampleCompute(VCO_bleptri_t *vco)
{
	int    j, k;
	float  freq, syncin;
	float  a, b, b1, db, p, t, w, dw, x, z;

	syncin  = vco->syncin;
	freq = vco->freq;
	p = vco->_p;  /* phase [0, 1) */
	w = vco->_w;  /* phase increment */
	b = vco->_b;  /* duty cycle (0, 1) */
	z = vco->_z;  /* low pass filter state */
	j = vco->_j;  /* index into buffer _f */
	k = vco->_k;  /* output state, 0 = positive slope, 1 = negative slope */

	if (vco->_init) {
		//		w = (exp2ap (freq[1] + vco->_port[OCTN] + vco->_port[TUNE] + expm[1] * vco->_port[EXPG] + 8.03136)
		//				+ 1e3 * linm[1] * vco->_port[LING]) / SAMPLERATE;
		w = freq / SAMPLERATE;
		if (w < 1e-5) w = 1e-5;
		if (w > 0.5) w = 0.5;
		b = 0.5 * (1.0 + vco->waveform);
		if (b < w) b = w;
		if (b > 1.0f - w) b = 1.0f - w;
		p = 0.5f * b;
		/* if we valued alias-free startup over low startup time, we could do:
		 *   p -= w;
		 *   place_slope_dd(_f, j, 0.0f, w, 1.0f / b); */
		k = 0;
		vco->_init = false;
	}

	//	a = 0.2 + 0.8 * vco->_port [FILT];
	a = 0.5f; // when a = 1, LPfilter is disabled

	t = freq / SAMPLERATE;
	if (t < 1e-5) t = 1e-5;
	if (t > 0.5) t = 0.5;
	dw = (t - w) ;
	t = 0.5 * (1.0 + vco->waveform );
	if (t < w) t = w;
	if (t > 1.0f - w) t = 1.0f - w;
	db = (t - b) ;

	w += dw;
	b += db;
	b1 = 1.0f - b;
	p += w;

	if (syncin >= 1e-20f) {  /* sync to master */

		float eof_offset = (syncin - 1e-20f) * w;
		float p_at_reset = p - eof_offset;
		p = eof_offset;
		//
		/* place any DDs that may have occurred in subsample before reset */
		if (!k) {
			x = -0.5f + p_at_reset / b;
			if (p_at_reset >= b) {
				x = 0.5f - (p_at_reset - b) / b1;
				place_slope_dd(vco->_f, j, p_at_reset - b + eof_offset, w, -1.0f / b1 - 1.0f / b);
				k = 1;
			}
			if (p_at_reset >= 1.0f) {
				p_at_reset -= 1.0f;
				x = -0.5f + p_at_reset / b;
				place_slope_dd(vco->_f, j, p_at_reset + eof_offset, w, 1.0f / b + 1.0f / b1);
				k = 0;
			}
		} else {
			x = 0.5f - (p_at_reset - b) / b1;
			if (p_at_reset >= 1.0f) {
				p_at_reset -= 1.0f;
				x = -0.5f + p_at_reset / b;
				place_slope_dd(vco->_f, j, p_at_reset + eof_offset, w, 1.0f / b + 1.0f / b1);
				k = 0;
			}
			if (!k && p_at_reset >= b) {
				x = 0.5f - (p_at_reset - b) / b1;
				place_slope_dd(vco->_f, j, p_at_reset - b + eof_offset, w, -1.0f / b1 - 1.0f / b);
				k = 1;
			}
		}

		/* now place reset DDs */
		if (k)
			place_slope_dd(vco->_f, j, p, w, 1.0f / b + 1.0f / b1);
		place_step_dd(vco->_f, j, p, w, -0.5f - x);
		x = -0.5f + p / b;
		k = 0;
		if (p >= b) {
			x = 0.5f - (p - b) / b1;
			place_slope_dd(vco->_f, j, p - b, w, -1.0f / b1 - 1.0f / b);
			k = 1;
		}
		vco->syncout = syncin;  /* best we can do is pass on upstream sync */

	} else if (!k) {  /* normal operation, slope currently up */

		x = -0.5f + p / b;
		if (p >= b) {
			x = 0.5f - (p - b) / b1;
			place_slope_dd(vco->_f, j, p - b, w, -1.0f / b1 - 1.0f / b);
			k = 1;
		}
		if (p >= 1.0f) {
			p -= 1.0f;
			vco->syncout = p / w + 1e-20f;
			x = -0.5f + p / b;
			place_slope_dd(vco->_f, j, p, w, 1.0f / b + 1.0f / b1);
			k = 0;
		} else {
			vco->syncout = 0.0f;
		}

	} else {  /* normal operation, slope currently down */

		x = 0.5f - (p - b) / b1;
		if (p >= 1.0f) {
			p -= 1.0f;
			vco->syncout = p / w + 1e-20f;
			x = -0.5f + p / b;
			place_slope_dd(vco->_f, j, p, w, 1.0f / b + 1.0f / b1);
			k = 0;
		} else {
			vco->syncout = 0.0f;
		}
		if (!k && p >= b) {
			x = 0.5f - (p - b) / b1;
			place_slope_dd(vco->_f, j, p - b, w, -1.0f / b1 - 1.0f / b);
			k = 1;
		}
	}
	vco->_f[j + DD_SAMPLE_DELAY] += x;

	z += a * (vco->_f[j] - z);
	vco->out = vco->amp * z;

	if (++j == FILLEN)
	{
		j = 0;
		memcpy (vco->_f, vco->_f + FILLEN, STEP_DD_PULSE_LENGTH * sizeof (float));
		memset (vco->_f + STEP_DD_PULSE_LENGTH, 0,  FILLEN * sizeof (float));
	}

	vco->_p = p;
	vco->_w = w;
	vco->_b = b;
	vco->_z = z;
	vco->_j = j;
	vco->_k = k;

	return vco->out;

}

/*********************************************************EOF***************************************************************/
