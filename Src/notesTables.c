/**
 ******************************************************************************
 * File Name          : notesTables.c
 * Author				: Xavier Halgand
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

#include "notesTables.h"

/* ********************************************************************************
 * 		Table of notes frequencies
 * 107 notes, first one is MIDI note #21 (A0), last one is #127 (G9)
 *
 * ********************************************************************************/

const float_t notesFreq[] =
{
/*  A0 --> */ 27.50000000, 29.13523509, 30.86770633,
		32.70319566, // <-- C1 (#24)
		34.64782887, 36.70809599, 38.89087297, 41.20344461,
		43.65352893, 46.24930284, 48.99942950, 51.91308720,
		55.00000000, 58.27047019, 61.73541266,
		65.40639133, // <-- C2
		69.29565774, 73.41619198, 77.78174593, 82.40688923,
		87.30705786, 92.49860568, 97.99885900, 103.82617439,
		110.00000000, 116.54094038, 123.47082531,
		130.81278265, //<-- C3
		138.59131549, 146.83238396, 155.56349186, 164.81377846,
		174.61411572, 184.99721136, 195.99771799, 207.65234879,
		220.00000000, 233.08188076, 246.94165063,
		261.62556530, // <-- C4
		277.18263098,293.66476792, 311.12698372, 329.62755691,
		349.22823143, 369.99442271, 391.99543598, 415.30469758,
		440.00000000, 466.16376152, 493.88330126,
		523.25113060, // <-- C5
		554.36526195, 587.32953583, 622.25396744, 659.25511383,
		698.45646287, 739.98884542, 783.99087196, 830.60939516,
		880.00000000, 932.32752304, 987.76660251,
		1046.50226120, // <-- C6
		1108.73052391, 1174.65907167, 1244.50793489, 1318.51022765,
		1396.91292573, 1479.97769085, 1567.98174393, 1661.21879032,
		1760.00000000, 1864.65504607, 1975.53320502,
		2093.00452240, // <-- C7
		2217.46104781, 2349.31814334, 2489.01586978, 2637.02045530,
		2793.82585146, 2959.95538169, 3135.96348785, 3322.43758064,
		3520.00000000, 3729.31009214, 3951.06641005,
		4186.00904481, // <-- C8
		4434.92209563, 4698.63628668, 4978.03173955, 5274.04091061,
		5587.65170293, 5919.91076339, 6271.92697571, 6644.87516128,
		7040.00000000, 7458.62018429, 7902.13282010,
		8372.01808962, // <-- C9
		8869.84419126, 9397.27257336, 9956.06347911, 10548.08182121,
		11175.30340586, 11839.82152677, 12543.85395142
};

/******************************************************************************/
/*
 * 				SCALES
 *
 *****************************************************************************/


/*  do ré mi sol la  */
const uint8_t MIDIscale01[] =
{
	5,// number of notes in this scale
	0,2,4,7,9
};

/*  do ré mib solb sol la  */
const uint8_t MIDIscale02[] =
{
	6,// number of notes in this scale
	0,2,3,6,7,9
};
/*   do ré mi fa sol la  */
const uint8_t MIDIscale03[] =
{
	6,// number of notes in this scale
	0,2,4,5,7,9
};

/* do ré fa la  */
const uint8_t MIDIscale04[] =
{
	4,// number of notes in this scale
	0,2,5,9
};

/* Gamme par ton : do# ré# fa sol la si */
const uint8_t MIDIscale05[] =
{
	6,// number of notes in this scale
	1,3,5,7,9,11
};

/* la mineur mélodique */
const uint8_t MIDIscale06[] =
{
/*		C	D	E	F	G#	A	B	*/
	7,// number of notes in this scale
	0,2,4,5,8,9,11
};


/*  do et sol */
const uint8_t MIDIscale07[] =
{
	2,// number of notes in this scale
	0,7
};

/*  do et la */
const uint8_t MIDIscale08[] =
{
	2,// number of notes in this scale
	0,9
};

/* C chord  */
const uint8_t MIDIscale09[] =
{
	3,// number of notes in this scale
	0,4,7
};

/* Dmin7 chord  */
const uint8_t MIDIscale10[] =
{
	4,// number of notes in this scale
	0,2,5,9
};

/*  do ré mi fa sol la  si */
const uint8_t MIDIscale11[] =
{
	7, // number of notes in this scale
	0,2,4,5,7,9,11
};

/*  the 12 notes */
const uint8_t MIDIscale12[] =
{
	12, // number of notes in this scale
	0,1,2,3,4,5,6,7,8,9,10,11
};


/*  do  */
const uint8_t MIDIscale13[] =
{
	1,// number of notes in this scale
	0
};

/* do ré */
const uint8_t MIDIscale14[] =
{
	2, // number of notes in this scale
	0,2
};
