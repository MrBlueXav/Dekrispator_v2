/**
 ******************************************************************************
 * File Name          : chorusFD.h
 * Author             : Xavier Halgand (thanks to Gabriel Rivas)
 * Date               :
 * Description        :
 ******************************************************************************
 */


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


#ifndef __CHORUSFD_H__
#define __CHORUSFD_H__

/*--------------------------------------------------------------------------------------*/

#include <stdint.h>
#include <math.h>
#include "sinetable.h"
#include <stdint.h>
#include "CONSTANTS.h"

/*--------------------------------------------------------------------------------------*/

#define DEPTH	 		1400 // Size of delay buffer, in samples : 29.17 ms
#define LEFT_DELAY 		240 /*  initial left delay */
#define RIGHT_DELAY 	240 /*  initial right delay */
#define LEFT_SWEEP		50
#define RIGHT_SWEEP		50
#define MAX_RATE		7.f // in Hz
#define MIN_RATE		0.02f // in Hz
#define LEFT_RATE		0.11f // in Hz
#define RIGHT_RATE		0.12f // in Hz
#define FEEDBACK		-0.2f // look at the diagram
#define FORWARD			0.5f
#define MIX				0.5f


/*---------------------------------------------------------------------------------------*/
typedef struct
{
	float 	amp;
	float 	freq;
	float 	phase;
	float 	out;

} Lfo_t;

/*---------------------------------------------------------------------------------------*/

typedef struct
{
	float		mix;       		/* delay blend parameter */
	float		fb;       		/* feedback volume */
	float		fw;       		/* delay tap mix volume */
	int32_t		in_idx;    		/* delay write index */
	float		dline[DEPTH] ;	/* delay buffer */
	float		baseDelay;		/* tap position */
	int8_t		mode; 			/* constant or variable delayed feedback ? */

} monochorus_t ;

/*---------------------------------------------------------------------------------------------*/
void Chorus_reset(uint8_t val);
void Chorus_init(void);
void ChorusDelay_init(monochorus_t *del, float delay_samples,float dfb,float dfw, float dmix);
void stereoChorus_compute (float * left_out, float * right_out, float in);

void inc_chorusFeedback(void);
void dec_chorusFeedback(void);
void ChorusFeedback_set(uint8_t val);

void inc_chorusRate(void);
void dec_chorusRate(void);
void ChorusRate_set(uint8_t val);
void ChorusSecondRate_set(uint8_t val);

void inc_chorusDelay(void);
void dec_chorusDelay(void);
void ChorusDelay_set(uint8_t val);

void inc_chorusSweep(void);
void dec_chorusSweep(void);
void ChorusSweep_set(uint8_t val);

void ChorusMode_toggle(void);
void ChorusMode_switch(uint8_t val);

void ChorusFDBsign_change(void);
void ChorusFDBsign_switch(uint8_t val);

void Delay_set_fb(monochorus_t *del, float val);
void Delay_set_fw(monochorus_t *del, float val);
void Delay_set_mix(monochorus_t *del, float val);
void Delay_set_delay(monochorus_t *del, float n_delay);
float Delay_get_fb(monochorus_t *del);
float Delay_get_fw(monochorus_t *del);
float Delay_get_mix(monochorus_t *del);

float mono_chorus_compute(monochorus_t *del, Lfo_t *lfo, float xin);

/*****************************************************************************************************/
#endif
