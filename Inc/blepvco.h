/**
 ******************************************************************************
 * File Name          	: blepvco.h
 * Author				: Xavier Halgand
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

#ifndef _BLEPVCO_H
#define _BLEPVCO_H

#include <stdbool.h>
#include "minblep_tables.h"
#include "CONSTANTS.h"

//----------------------------------------------------------------------------------------------------------

enum { FILLEN = 256 };

//----------------------------------------------------------------------------------------------------------

void place_step_dd(float *buffer, int index, float phase, float w, float scale);
void place_slope_dd(float *buffer, int index, float phase, float w, float slope_delta);

//----------------------------------------------------------------------------------------------------------

//class VCO_blepsaw

typedef struct
{
	float	out;
	float	amp;
	float	last_amp;
	float 	freq;
	float	syncin;
	float	syncout;
	float   _p, _w, _z;
	float   _f [FILLEN + STEP_DD_PULSE_LENGTH];
	int     _j;
	bool	_init;

} VCO_blepsaw_t;

void VCO_blepsaw_Init(VCO_blepsaw_t *vco);
float VCO_blepsaw_SampleCompute(VCO_blepsaw_t *vco);

//----------------------------------------------------------------------------------------------------------

//	class VCO_bleprect

typedef struct
{
	float	out;
	float	amp;
	float	last_amp;
	float 	freq;
	float	waveform;	// duty cycle, must be in [-1, 1]
	float	syncin;
	float	syncout;
	float   _p, _w, _b, _x, _z;
	float   _f [FILLEN + STEP_DD_PULSE_LENGTH];
	int     _j, _k;
	bool	_init;

} VCO_bleprect_t ;

void VCO_bleprect_Init(VCO_bleprect_t *vco);
float VCO_bleprect_SampleCompute(VCO_bleprect_t *vco);

//----------------------------------------------------------------------------------------------------------

//		class VCO_bleptri

typedef struct
{
	float	out;
	float	amp;
	float	last_amp;
	float 	freq;
	float	waveform;	// duty cycle, must be in [-1, 1]
	float	syncin;
	float	syncout;
	float   _p, _w, _b, _z;
	float   _f [FILLEN + LONGEST_DD_PULSE_LENGTH];
	int     _j, _k;
	bool	_init;

} VCO_bleptri_t ;

void VCO_bleptri_Init(VCO_bleptri_t *vco);
float VCO_bleptri_SampleCompute(VCO_bleptri_t *vco);

#endif /* _BLEPVCO_H */
