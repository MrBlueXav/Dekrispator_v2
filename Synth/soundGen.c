/**
 ******************************************************************************
 * File Name          : soundGen.c
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

#include "soundGen.h"

/*-------------------------------------------------------*/

#define EPSI				.00002f
//#define MAX_SOUNDS			14 // number - 1 of different sounds (starts at 0)

/*-------------------------------------------------------*/

extern bool demoMode;
extern bool freeze;
extern bool sequencerIsOn;

extern Sequencer_t seq;
extern NoteGenerator_t noteGen;

extern Oscillator_t op1;
extern Oscillator_t op2;
extern Oscillator_t op3;
extern Oscillator_t op4;

extern VCO_blepsaw_t mbSawOsc;
extern VCO_bleprect_t mbRectOsc;
extern VCO_bleptri_t mbTriOsc;

extern Oscillator_t vibr_lfo;
extern Oscillator_t filt_lfo;
extern Oscillator_t filt2_lfo;
extern Oscillator_t amp_lfo;

extern ResonantFilter SVFilter;
extern ResonantFilter SVFilter2;
extern float filterFreq;
extern float filterFreq2;

extern ADSR_t adsr;
extern int8_t currentNote;
extern int8_t velocity;

/*--------------------------------------------------------------*/

static bool autoFilterON _CCM_;
static bool delayON _CCM_;
static bool phaserON _CCM_;
static bool chorusON _CCM_;
static int8_t autoSound _CCM_;

static float f0 _CCM_;
static float vol _CCM_;
static float env _CCM_;
static enum timbre sound _CCM_;

/*===============================================================================================================*/

void autoSound_set(int8_t val) {
	autoSound = val;
}
/*---------------------------------------------------------*/
void RandSound1(uint8_t val) /* random series of tones */
{
	if (val == MIDI_MAXi) {
		if (autoSound == 0)
			autoSound = 1;
		else
			autoSound = 0;
	}
}
/*---------------------------------------------------------*/
void RandSound2(uint8_t val) /* random series of tones */
{
	if (val == MIDI_MAXi) {
		if (autoSound == 0)
			autoSound = 2;
		else
			autoSound = 0;
	}
}
/*---------------------------------------------------------*/
uint8_t soundNumber_get(void) {
	return sound;
}
/*---------------------------------------------------------*/
void Parameter_fine_tune(uint8_t val) {

}
/*---------------------------------------------------------*/
void DemoMode_toggle(uint8_t val) {
	if (val == MIDI_MAXi) {
		demoMode = !demoMode;
	}
}
/*---------------------------------------------------------*/
void Sequencer_toggle(uint8_t val) { // run or stop sequencer
	if (val == MIDI_MAXi) {
		sequencerIsOn = !sequencerIsOn;
		if(!sequencerIsOn) 
			ADSR_keyOff(&adsr);
			Reset_notes_On();
		BSP_LED_Toggle(LED_Red);
	}
}
/*---------------------------------------------------------*/
void Synth_reset(uint8_t val) {
	if (val == MIDI_MAXi) {
		demoMode = false;
		freeze = false;
		Synth_Init();
	}
}

/*-------------------------------------------------------*/
void AmpLFO_amp_set(uint8_t val) {
	amp_lfo.amp = val / MIDI_MAX;
}
/*-------------------------------------------------------*/
void AmpLFO_freq_set(uint8_t val) {
	amp_lfo.freq = MAX_VIBRATO_FREQ / MIDI_MAX * val;
}
/*-------------------------------------------------------*/
void Filt1LFO_amp_set(uint8_t val) {
	filt_lfo.amp = MAX_FILTER_LFO_AMP / MIDI_MAX * val;
}
/*-------------------------------------------------------*/
void Filt1LFO_freq_set(uint8_t val) {
	filt_lfo.freq = MAX_VIBRATO_FREQ / MIDI_MAX * val;
}
/*-------------------------------------------------------*/
void Filt2LFO_amp_set(uint8_t val) {
	filt2_lfo.amp = MAX_FILTER_LFO_AMP / MIDI_MAX * val;
}
/*-------------------------------------------------------*/
void Filt2LFO_freq_set(uint8_t val) {
	filt2_lfo.freq = MAX_VIBRATO_FREQ / MIDI_MAX * val;
}

/*-------------------------------------------------------*/
void toggleVibrato(void) {
	if (vibr_lfo.amp != 0) {
		vibr_lfo.last_amp = vibr_lfo.amp;
		vibr_lfo.amp = 0;
	} else
		vibr_lfo.amp = vibr_lfo.last_amp;
}
/*-------------------------------------------------------*/
void VibratoAmp_set(uint8_t val) {
	vibr_lfo.amp = MAX_VIBRATO_AMP / MIDI_MAX * val;
}
/*-------------------------------------------------------*/
void VibratoFreq_set(uint8_t val) {
	vibr_lfo.freq = MAX_VIBRATO_FREQ / MIDI_MAX * val;
}
/*-------------------------------------------------------*/
void toggleSynthOut(void) {
	if (op1.amp != 0) {
		op1.last_amp = op1.amp;
		op1.amp = 0;
		op2.last_amp = op2.amp;
		op2.amp = 0;
		op3.last_amp = op3.amp;
		op3.amp = 0;
	} else {
		op1.amp = op1.last_amp;
		op2.amp = op2.last_amp;
		op3.amp = op3.last_amp;
	}
}
/*-------------------------------------------------------*/
void SynthOut_switch(uint8_t val) {
	switch (val) {
	case MIDI_MAXi:
		op1.amp = op1.last_amp;
		op2.amp = op2.last_amp;
		op3.amp = op3.last_amp;
		mbSawOsc.amp = mbSawOsc.last_amp;
		mbRectOsc.amp = mbRectOsc.last_amp;
		mbTriOsc.amp = mbTriOsc.last_amp;
		break;

	case 0:
		op1.last_amp = op1.amp;
		op1.amp = 0;
		op2.last_amp = op2.amp;
		op2.amp = 0;
		op3.last_amp = op3.amp;
		op3.amp = 0;
		mbSawOsc.last_amp = mbSawOsc.amp;
		mbSawOsc.amp = 0;
		mbRectOsc.last_amp = mbRectOsc.amp;
		mbRectOsc.amp = 0;
		mbTriOsc.last_amp = mbTriOsc.amp;
		mbTriOsc.amp = 0;
		break;
	}
}

/*-------------------------------------------------------*/
void incSynthOut(void) {
	op1.amp *= 1.2f;
	op2.amp *= 1.2f;
	op3.amp *= 1.2f;
}
/*-------------------------------------------------------*/
void decSynthOut(void) {
	op1.amp *= .8f;
	op2.amp *= .8f;
	op3.amp *= .8f;
}
/*-------------------------------------------------------*/
void SynthOut_amp_set(uint8_t val) {
	float_t amp;
	amp = (val * 5.f / MIDI_MAX) * (val * 5.f / MIDI_MAX);
	op1.amp = amp;
	op2.amp = amp;
	op3.amp = amp;
	mbSawOsc.amp = amp;
	mbRectOsc.amp = amp;
	mbTriOsc.amp = amp;
}
/*-------------------------------------------------------*/
void Delay_toggle(void) {
	if (delayON) {
		delayON = false;
		Delay_clean();
	} else
		delayON = true;
}
/*-------------------------------------------------------*/
void Delay_switch(uint8_t val) {

	if (val > 63)
		delayON = true;
	else {
		delayON = false;
		Delay_clean();
	}
}
/*-------------------------------------------------------*/
void toggleFilter(void) {
	if (autoFilterON)
		autoFilterON = false;
	else
		autoFilterON = true;
}
/*-------------------------------------------------------*/
void Filter_Random_switch(uint8_t val) {
	if (val > 63)
		autoFilterON = true;
	else
		autoFilterON = false;
}
/*-------------------------------------------------------*/
void Chorus_toggle(void) {
	if (chorusON)
		chorusON = false;
	else
		chorusON = true;
}
/*-------------------------------------------------------*/
void Chorus_switch(uint8_t val) {

	if (val > 63)
		chorusON = true;
	else
		chorusON = false;
}
/*-------------------------------------------------------*/
void Phaser_switch(uint8_t val) {

	if (val > 63)
		phaserON = true;
	else
		phaserON = false;
}
/*-------------------------------------------------------*/
void nextSound(void) {
	if (sound < LAST_SOUND)
		(sound)++;
	else
		sound = LAST_SOUND;
}
/*-------------------------------------------------------*/
void prevSound(void) {
	if (sound > 0)
		(sound)--;
	else
		sound = 0;
}
/*-------------------------------------------------------*/
void Sound_set(uint8_t val) {
	sound = (uint8_t) rintf((LAST_SOUND - 1) / MIDI_MAX * val);
	if (sound != ADDITIVE)
		AdditiveGen_newWaveform();
}
/*******************************************************************************************************************************/

void FM_OP1_freq_set(uint8_t val) {
	FM_op_freq_set(&op1, val);
}
/*-------------------------------------------------------*/
void FM_OP1_modInd_set(uint8_t val) {
	FM_op_modInd_set(&op1, val);
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void FM_OP2_freq_set(uint8_t val) {
	//FM_op_freq_set(&op2, val);
	op2.mul = Lin2Exp(val, 0.2f, 32.f); // the freq of op2 is a multiple of the main pitch freq (op1)
	//op2.mul = roundf(32 * val/MIDI_MAX);
}
/*-------------------------------------------------------*/
void FM_OP2_freqMul_inc(uint8_t val) {
	if (val == MIDI_MAXi) {
		op2.mul *= 1.01f;
	}
}
/*-------------------------------------------------------*/
void FM_OP2_freqMul_dec(uint8_t val) {
	if (val == MIDI_MAXi) {
		op2.mul *= 0.99f;
	}
}
/*-------------------------------------------------------*/
void FM_OP2_modInd_set(uint8_t val) {
	FM_op_modInd_set(&op2, val);
}

/*------------------------------------------------------------------------------------------------------------------------------*/
void FM_OP3_freq_set(uint8_t val) {
	op3.mul = Lin2Exp(val, 0.2f, 32.f); // the freq of op3 is a multiple of the main pitch freq (op1)
}
/*-------------------------------------------------------*/
void FM_OP3_modInd_set(uint8_t val) {
	FM_op_modInd_set(&op3, val);
}
/*-------------------------------------------------------*/
void FM_OP3_freqMul_inc(uint8_t val) {
	if (val == MIDI_MAXi) {
		op3.mul *= 1.01f;
	}
}
/*-------------------------------------------------------*/
void FM_OP3_freqMul_dec(uint8_t val) {
	if (val == MIDI_MAXi) {
		op3.mul *= 0.99f;
	}
}

/*--------------------------------------------------------------------------------------------------------------------------*/
void FM_OP4_freq_set(uint8_t val) {
	op4.mul = Lin2Exp(val, 0.2f, 32.f); // the freq of op4 is a multiple of the main pitch freq (op1)
}
/*-------------------------------------------------------*/
void FM_OP4_modInd_set(uint8_t val) {
	FM_op_modInd_set(&op4, val);
}
/*-------------------------------------------------------*/
void FM_OP4_freqMul_inc(uint8_t val) {
	if (val == MIDI_MAXi) {
		op4.mul *= 1.01f;
	}
}
/*-------------------------------------------------------*/
void FM_OP4_freqMul_dec(uint8_t val) {
	if (val == MIDI_MAXi) {
		op4.mul *= 0.99f;
	}
}

/*===============================================================================================================*/

void Synth_Init(void) {

	vol = env = 1;
	sound = MORPH_SAW;
	autoFilterON = false;
	autoSound = 0;
	chorusON = false;
	delayON = false;
	phaserON = false;

	Delay_init();
	drifter_init();
	//pitchGen_init();
	sequencer_init();
	ADSR_init(&adsr);
	Chorus_init();
	PhaserInit();
	SVF_init();
	filterFreq = 0.25f;
	filterFreq2 = 0.25f;
	osc_init(&op1, 0.8f, 587.f);
	osc_init(&op2, 0.8f, 587.f);
	osc_init(&op3, 0.8f, 587.f);
	osc_init(&op4, 0.8f, 587.f);
	osc_init(&vibr_lfo, 0, VIBRATO_FREQ);
	osc_init(&filt_lfo, 0, 0);
	osc_init(&filt2_lfo, 0, 0);
	osc_init(&amp_lfo, 0, 0);
	AdditiveGen_newWaveform();
	VCO_blepsaw_Init(&mbSawOsc);
	VCO_bleprect_Init(&mbRectOsc);
	VCO_bleptri_Init(&mbTriOsc);
}
/*---------------------------------------------------------------------------------------*/

void sequencer_newStep_action(void) // User callback function called by sequencer_process()
{
	if ((noteGen.automaticON || noteGen.chRequested)) {
		seq_sequence_new();
		noteGen.chRequested = false;
		AdditiveGen_newWaveform();
	}

	if ((noteGen.someNotesMuted) && (rintf(frand_a_b(0.4f, 1)) == 0))
		ADSR_keyOff(&adsr);
	else
		ADSR_keyOn(&adsr);

	if (autoFilterON)
		SVF_directSetFilterValue(&SVFilter,
		Ts * 600.f * powf(5000.f / 600.f, frand_a_b(0, 1)));

	if (noteGen.transpose != 0) {
		noteGen.rootNote += noteGen.transpose;
		seq_transpose();
	}

	if (autoSound == 1) {
		switch (rand() % 4) // 4 random timbers
		{
		case 0:
			sound = CHORD15;
			break;
		case 1:
			AdditiveGen_newWaveform();
			sound = ADDITIVE;
			break;
		case 2:
			sound = CHORD13min5;
			break;
		case 3:
			sound = VOICES3;
			break;
		}
	}
	if (autoSound == 2) {
		sound = rand() % LAST_SOUND;
		if ((sound == CHORD13min5) || (sound == CHORD135))
			sound = VOICES3;
		if (sound == ADDITIVE)
			AdditiveGen_newWaveform();
	}

	f0 = notesFreq[seq.track1.note[seq.step_idx]]; // Main "melody" frequency
	vol = frand_a_b(0.4f, .8f); // slightly random volume for each note
}
/*---------------------------------------------------------------------------------------*/

void sequencer_newSequence_action(void) // User callback function called by sequencer_process()
{
	/* A new sequence begins ... */
	if ((demoMode == true) && (freeze == false)) {
		MagicPatch(MIDI_MAXi);
		MagicFX(MIDI_MAXi);
	}
}
/*===============================================================================================================*/

void make_sound(uint16_t *buf, uint16_t length) // To be used with the Sequencer
{

	uint16_t pos;
	uint16_t *outp;
	float y = 0;
	float yL, yR;
	float f1;
	uint16_t valueL, valueR;

	outp = buf;

	for (pos = 0; pos < length; pos++) {
		/*--- Sequencer actions and update ---*/
		//sequencer_process(); //computes f0 and calls sequencer_newStep_action() and sequencer_newSequence_action()
		// GRA
		if (sequencerIsOn == true) {
			sequencer_process(); //computes f0 and calls sequencer_newStep_action() and sequencer_newSequence_action()
		} else {
			f0 = notesFreq[currentNote];
			vol = (float) velocity / 127.0f;
		}

		/*--- compute vibrato modulation ---*/
		f1 = f0 * (1 + Osc_WT_SINE_SampleCompute(&vibr_lfo));

		/*--- Generate waveform ---*/
		y = waveCompute(sound, f1);

		/*--- Apply envelop and tremolo ---*/
		env = ADSR_computeSample(&adsr)
				* (1 + Osc_WT_SINE_SampleCompute(&amp_lfo));
		y *= vol * env; // apply volume and envelop

		//if (adsr.cnt_ >= seq.gateTime)			ADSR_keyOff(&adsr);

		// GRA

		if (sequencerIsOn == true) {
			if (adsr.cnt_ >= seq.gateTime)
				ADSR_keyOff(&adsr);
		}

		/*--- Apply filter effect ---*/
		/* Update the filters cutoff frequencies */
		if ((!autoFilterON) && (filt_lfo.amp != 0))
			SVF_directSetFilterValue(&SVFilter,
					filterFreq * (1 + OpSampleCompute7bis(&filt_lfo)));
		if (filt2_lfo.amp != 0)
			SVF_directSetFilterValue(&SVFilter2,
					filterFreq2 * (1 + OpSampleCompute7bis(&filt2_lfo)));
		y =
				0.5f
						* (SVF_calcSample(&SVFilter, y)
								+ SVF_calcSample(&SVFilter2, y)); // Two filters in parallel

		/*---  Apply delay effect ----*/
		if (delayON)
			y = Delay_compute(y);

		/*---  Apply phaser effect ----*/
		if (phaserON)
			y = Phaser_compute(y);

		/*--- Apply chorus/flanger effect ---*/
		if (chorusON)
			stereoChorus_compute(&yL, &yR, y);
		else
			yL = yR = y;

		/*--- clipping ---*/
		yL = (yL > 1.0f) ? 1.0f : yL; //clip too loud left samples
		yL = (yL < -1.0f) ? -1.0f : yL;

		yR = (yR > 1.0f) ? 1.0f : yR; //clip too loud right samples
		yR = (yR < -1.0f) ? -1.0f : yR;

		/****** let's hear the new sample *******/

		valueL = (uint16_t) ((int16_t) ((32767.0f) * yL)); // conversion float -> int
		valueR = (uint16_t) ((int16_t) ((32767.0f) * yR));

		*outp++ = valueL; // left channel sample
		*outp++ = valueR; // right channel sample
	}

}

