/**
 ******************************************************************************
 * File Name          : sequencer.c
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
/*********************************************************************************************/

#include "sequencer.h"

/*--------------------------------------------------------------------------------------------*/

Sequencer_t 		seq _CCM_;
NoteGenerator_t 	noteG _CCM_;

/*--------------------------------------------------------------------------------------------*/

void seq_gateTime_set(uint8_t val) // val is a number of samples
{
	seq.gateTime = seq.steptime * ((0.9f - 0.1f) * val / MIDI_MAX + 0.1f); // from 10% to 90% of each step duration
}
/*-------------------------------------------------------*/
void seq_transpUp(void) // one tone up
{
	if (noteG.rootNote < (MAX_NOTE_INDEX - 12))
	{
		noteG.transpose = 2;
	}
}
/*-------------------------------------------------------*/
void seq_transp(int8_t semitone, uint8_t val)
{
	if (val == MIDI_MAXi)
	{
		noteG.transpose = semitone;
	}
}
/*-------------------------------------------------------*/
void seq_transpDown(void) // one tone down
{
	if (noteG.rootNote > FIRST_NOTE)
	{
		noteG.transpose = -2;
	}
}

/*-------------------------------------------------------*/
void seq_chooseScale(int16_t idx)
{
	uint8_t		*currentScale ;

	switch (idx)
	{
	case 0 : 	currentScale = (uint8_t*)MIDIscale13;	break ;
	case 1 :  	currentScale = (uint8_t*)MIDIscale14;	break;
	case 2 : 	currentScale = (uint8_t*)MIDIscale07;	break;
	case 3 : 	currentScale = (uint8_t*)MIDIscale08;	break;
	case 4 : 	currentScale = (uint8_t*)MIDIscale09;	break;
	case 5 : 	currentScale = (uint8_t*)MIDIscale10;	break;
	case 6 : 	currentScale = (uint8_t*)MIDIscale04;	break;
	case 7 : 	currentScale = (uint8_t*)MIDIscale01;	break;
	case 8 : 	currentScale = (uint8_t*)MIDIscale03;	break;
	case 9 : 	currentScale = (uint8_t*)MIDIscale11;	break;
	case 10 : 	currentScale = (uint8_t*)MIDIscale02;	break;
	case 11 : 	currentScale = (uint8_t*)MIDIscale06;	break;
	case 12 : 	currentScale = (uint8_t*)MIDIscale05;	break;
	case 13 : 	currentScale = (uint8_t*)MIDIscale12;	break;
	case 14 : 	currentScale = (uint8_t*)MIDIscale11;	break;
	default :	currentScale = (uint8_t*)MIDIscale11; break ;
	}
	noteG.currentScale = currentScale;
	noteG.chRequested = true;
}
/*-------------------------------------------------------*/
void seq_nextScale(void)
{
	if (noteG.scaleIndex < MAX_SCALE_INDEX)
	{
		noteG.scaleIndex++;
		seq_chooseScale(noteG.scaleIndex);
	}
}
/*-------------------------------------------------------*/
void seq_prevScale(void)
{
	if (noteG.scaleIndex > 0)
	{
		noteG.scaleIndex--;
		seq_chooseScale(noteG.scaleIndex);
	}
}
/*-------------------------------------------------------*/
void seq_scale_set(uint8_t val)
{
	noteG.scaleIndex = (uint8_t) rintf(MAX_SCALE_INDEX / MIDI_MAX * val);
	seq_chooseScale(noteG.scaleIndex);
}
/*-------------------------------------------------------*/
void seq_automatic_or_manual(void)
{
	if (noteG.automaticON) noteG.automaticON = false;
	else noteG.automaticON = true;
}
/*-------------------------------------------------------*/
void seq_switchMovingSeq(uint8_t val)
{
	if (val > 63)
		noteG.automaticON = true;
	else
		noteG.automaticON= false;
}
/*-------------------------------------------------------*/
void seq_toggleGlide(void)
{
	if (noteG.glideON) noteG.glideON = false;
	else noteG.glideON = true;
}
/*-------------------------------------------------------*/
void seq_switchGlide(uint8_t val)
{
	switch (val)
	{
	case MIDI_MAXi : 	noteG.glideON = true; break;
	case 0 : 	noteG.glideON = false; break;
	}
}
/*-------------------------------------------------------*/
void seq_muteSomeNotes(void)
{
	if (noteG.someNotesMuted) noteG.someNotesMuted = false;
	else noteG.someNotesMuted = true;
}
/*-------------------------------------------------------*/
void seq_switchMute(uint8_t val)
{
	switch (val)
	{
	case MIDI_MAXi : 	noteG.someNotesMuted = true; break;
	case 0 : 	noteG.someNotesMuted = false; break;
	}
}
/*-------------------------------------------------------*/
void seq_doubleTempo(void)
{
	//if (noteG.freq <= 5) noteG.freq *= 2;
}
/*-------------------------------------------------------*/
void seq_halfTempo(void)
{
	//if (noteG.freq >= .05f) noteG.freq *= 0.5f;
}
/*-------------------------------------------------------*/
void seq_incTempo(void)
{
	//if (noteG.freq <= 5) noteG.freq += 0.01f;
}

/*-------------------------------------------------------*/
void seq_decTempo(void)
{
	//if (noteG.freq >= .05f) noteG.freq -= 0.01f;
}
/*-------------------------------------------------------*/
void seq_incMaxFreq(void)
{
	if (noteG.octaveSpread < 8)
	{
		noteG.octaveSpread++;
		noteG.chRequested = true;
		//pitchGenChangePoints();
	}
}
/*-------------------------------------------------------*/
void seq_decMaxFreq(void)
{
	if (noteG.octaveSpread > 0)
	{
		noteG.octaveSpread--;
		noteG.chRequested = true;
		//pitchGenChangePoints();
	}
}
/*-------------------------------------------------------*/
void seq_freqMax_set(uint8_t val)
{
	noteG.octaveSpread = (uint8_t)(8/MIDI_MAX * val);
	noteG.chRequested = true;
}
/*-------------------------------------------------------*/
void seq_tempo_set(uint8_t val)
{
	seq.tempo = (float)(500.f * val / MIDI_MAX + 20); // unit : bpm
	seq.steptime = lrintf(SAMPLERATE * 60 / seq.tempo);
	//seq.smp_count = seq.steptime;
}
/*--------------------------------------------------------------------------------------------*/
void seq_sequence_new(void)
{
	int16_t relativeNote;
	int16_t octaveShift;
	int16_t index;

	for (uint8_t i = 0; i < NUMBER_STEPS; i++)
	{
		relativeNote = noteG.currentScale[lrintf(frand_a_b(1 , noteG.currentScale[0]))];
		octaveShift = 12 * lrintf(frand_a_b(0 , noteG.octaveSpread));
		index = noteG.rootNote + octaveShift + relativeNote - FIRST_NOTE;

		while (index > MAX_NOTE_INDEX) index -= 12;
		while (index < 0) index += 12;
		seq.track1.note[i] = index; // note frequency is in notesFreq[index]
	}
}
/*--------------------------------------------------------------------------------------------*/
void seq_transpose(void)
{
	int16_t  noteIndex;

	for (uint8_t i = 0; i < NUMBER_STEPS; i++)
	{
		noteIndex = seq.track1.note[i] + noteG.transpose;
		while (noteIndex > MAX_NOTE_INDEX) noteIndex -= 12;
		while (noteIndex < 0) noteIndex += 12;
		seq.track1.note[i] =  noteIndex;
	}
	noteG.transpose = 0;
}
/*--------------------------------------------------------------------------------------------*/
void sequencer_init(void)
{
	seq.tempo = INIT_TEMPO;
	seq.steptime = lrintf(SAMPLERATE * 60 / seq.tempo);
	seq.smp_count = 0;
	seq.step_idx = 0;
	seq.gateTime = seq.steptime / 2 ;

	noteG.transpose = 0;
	noteG.automaticON = false;
	noteG.glideON = false;
	noteG.chRequested = false;
	noteG.someNotesMuted = false;
	noteG.scaleIndex = 0;
	noteG.octaveSpread = 4;
	noteG.rootNote = 36;
	noteG.currentScale = (uint8_t*)MIDIscale13;

	seq_sequence_new();
}
/*--------------------------------------------------------------------------------------------*/
void sequencer_process(void) // To be called at each sample treatment
{
	/* If we have reached a new step ....  */
	if (seq.smp_count-- <= 0)
	{
		/* If we are at the begining of a new sequence .... */
		if (seq.step_idx == 0)
		{
			sequencer_newSequence_action();
		}
		sequencer_newStep_action();

		seq.smp_count = seq.steptime; // reload the counter
		seq.step_idx++;
		if(seq.step_idx >= NUMBER_STEPS) seq.step_idx = 0;

	}
}
/*--------------------------------------------------------------------------------------------*/
