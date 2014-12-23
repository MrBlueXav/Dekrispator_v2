/**
 ******************************************************************************
 * File Name          : notesTables.h
 * Author				: Xavier Halgand
 * Date               :
 * Description        :
 ******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NOTESTABLES_H
#define __NOTESTABLES_H

/* Includes ------------------------------------------------------------------*/

#include <math.h>
#include <stdint.h>

/*--------------------- Global Defines ------------------------ */

#define MAX_SCALE_INDEX		14	/* starting at 0 ! */
#define FIRST_NOTE			21  /* MIDI number */
#define MAX_NOTE_INDEX		106	/* starting at 0 ! */


/*---------------------------------------------------------------------------*/
extern const float_t notesFreq[];
extern const uint8_t MIDIscale01[];
extern const uint8_t MIDIscale02[];
extern const uint8_t MIDIscale03[];
extern const uint8_t MIDIscale04[];
extern const uint8_t MIDIscale05[];
extern const uint8_t MIDIscale06[];
extern const uint8_t MIDIscale07[];
extern const uint8_t MIDIscale08[];
extern const uint8_t MIDIscale09[];
extern const uint8_t MIDIscale10[];
extern const uint8_t MIDIscale11[];
extern const uint8_t MIDIscale12[];
extern const uint8_t MIDIscale13[];
extern const uint8_t MIDIscale14[];

/*---------------------------------------------------------------------------*/

#endif
