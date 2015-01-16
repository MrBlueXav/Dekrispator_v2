/**
 ******************************************************************************
 * File Name          : drifter.h
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

#ifndef __DRIFTER_H__
#define __DRIFTER_H__
/************************************************************************************/
#include  <stdint.h>
#include "random.h"
#include "CONSTANTS.h"

/*---------------------------------------------------------------------------------*/
typedef struct
{
	/*--- parameters ----*/
	float 	    fmax; // sort of max frequency
	float   	fmin; // sort of min frequency
	float   	gain; // drifter output is bound in [-gain, +gain]

	/*---- internals -----*/
	float 		minLength;
	float 		maxLength;
	uint32_t    length;
	uint32_t    n; //sample counter
	float		initial;
	float       final;
	float       slope;

	/*--- output ---*/
	float    	out;

} Drifter_t;

/*----------------------------------------------------------------------------------*/
void 	drifter_init (void) ;
float 	drifter_nextSample(Drifter_t *d);
float 	d1_drifter_nextSample(void) ;
float 	d2_drifter_nextSample(void) ;
void	Drifter_amp_set(uint8_t val);
void	Drifter_minFreq_set(uint8_t val);
void	Drifter_maxFreq_set(uint8_t val);


/************************************************************************************/
#endif
