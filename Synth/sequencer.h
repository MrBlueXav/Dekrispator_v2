/**
 ******************************************************************************
 * File Name          	: sequencer.h
 * Author				: Xavier Halgand
 * Date               	:
 * Description        	:
 ******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SEQUENCER_H
#define __SEQUENCER_H

/*----------------------------------------------------------------------------*/

#include <stdint.h>
#include <math.h>
#include <stdbool.h>

#include "CONSTANTS.h"
#include "random.h"
#include "notesTables.h"

/*-----------------------------------------------------------------------------*/

#define NUMBER_STEPS 	16
#define INIT_TEMPO 		(4*80)

/*------------------------------------------------------------------------------*/
typedef struct
{
	uint8_t		note[NUMBER_STEPS]; //
	uint8_t		veloc[NUMBER_STEPS]; //

} Track_t;
/*------------------------------------------------------------------------------*/
typedef struct
{
	Track_t 	track1;
	float_t 	tempo; 		// unit : bpm
	int32_t 	steptime; 	// unit : # of samples
	int32_t 	smp_count;	// sample counter
	uint8_t		step_idx;	// current step index
	uint32_t 	gateTime; 	// desired gate on time (in samples)

} Sequencer_t;
/*------------------------------------------------------------------------------*/
typedef struct
{
	uint8_t 	scaleIndex ;
	uint8_t		*currentScale ;
	uint8_t		octaveSpread;
	uint8_t		rootNote;
	int8_t 		transpose;
	bool 		automaticON;	// random notes ?
	bool		glideON;		// glissando between notes ?
	bool		chRequested;
	bool		someNotesMuted;

} NoteGenerator_t;

/*--------------   Exported Functions Prototype ---------------------------*/

void seq_tempo_set(uint8_t val);
void sequencer_init(void);
void sequencer_process(void);
void seq_sequence_new(void);
void seq_transpose(void);
void seq_transpUp(void); // one tone up
void seq_transpDown(void); // one tone down
void seq_transp(int8_t s, uint8_t val);
void seq_gateTime_set(uint8_t val);
void seq_chooseScale(uint8_t idx);
void seq_scale_set(uint8_t val);
void seq_switchMovingSeq(uint8_t val);
void seq_switchMute(uint8_t val);
void seq_switchGlide(uint8_t val);
void seq_doubleTempo(void);
void seq_halfTempo(void);
void seq_incTempo(void);
void seq_decTempo(void);
void seq_freqMax_set(uint8_t val);


/* User Callbacks: user has to implement these functions in his code if
  they are needed. -----------------------------------------------------------*/
void sequencer_newSequence_action(void);
void sequencer_newStep_action(void);

/******************************************************************************/
#endif




