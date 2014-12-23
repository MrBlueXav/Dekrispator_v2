/**
 ******************************************************************************
 * File Name          : drifter.h
 * Author			  : Xavier Halgand
 * Date               :
 * Description        :
 ******************************************************************************
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
