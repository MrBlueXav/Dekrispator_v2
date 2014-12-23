/* blepvco - minBLEP-based, hard-sync-capable LADSPA VCOs.
 *
 * Copyright (C) 2004-2005 Sean Bolton.
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

#ifndef _MINBLEP_TABLES_H
#define _MINBLEP_TABLES_H

/* minBLEP constants */
/* minBLEP table oversampling factor (must be a power of two): */
#define MINBLEP_PHASES          64
/* MINBLEP_PHASES minus one: */
#define MINBLEP_PHASE_MASK      63
/* length in samples of (truncated) step discontinuity delta: */
#define STEP_DD_PULSE_LENGTH    72
/* length in samples of (truncated) slope discontinuity delta: */
#define SLOPE_DD_PULSE_LENGTH   71
/* the longer of the two above: */
#define LONGEST_DD_PULSE_LENGTH STEP_DD_PULSE_LENGTH
/* delay between start of DD pulse and the discontinuity, in samples: */
#define DD_SAMPLE_DELAY          4

typedef struct { float value, delta; } float_value_delta;

/* in minblep_tables.c: */
extern const float_value_delta step_dd_table[];
extern const float             slope_dd_table[];

#endif /* _MINBLEP_TABLES_H */
