/**
 * Super OSD, software revision 3
 * Copyright (C) 2010 Thomas Oldbury
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef	OSD_H
#define	OSD_H

// move this to another file?
#define _MY_ISR __attribute__((interrupt, shadow, no_auto_psv))

#define FORMAT_PAL  0
#define FORMAT_NTSC 1

// These values are from trial and error.
#define PAL_GFX_SCALE_192	116
#define NTSC_GFX_SCALE_192	96
#define PAL_GFX_SCALE_256	180
#define NTSC_GFX_SCALE_256	148

#include "gfx.h"
#include "osd.h"

extern char tv_format, tv_format_switch;
extern unsigned int tv_field, tv_line, tv_max_line;
extern long int tv_time;

/**
 * The OSD files handle the actual output of the graphics framebuffer
 * as an overlay on the video signal.
 */

/* Storing the current time */
/*
struct OSDTime
{
	unsigned char hour, minute, second;
	unsigned long total_seconds; // 32-bit seconds ticker
};
*/

/* Current input signal state. */
/*
struct OSDState
{
	// Number of lines so far.
	int line_count;
	// Number of lines in the last field.
	// This is used to determine whether or not the signal is PAL or NTSC.
	int line_count_last;
	// Current field count. (up to 4.1 billion.)
	unsigned long field_count;
	// Run time.
	struct OSDTime run_time;
};
*/

/* Function prototypes. */
void init_osd();
void setup_pll();
void setup_io();
void setup_int();
void disable_int();
void _MY_ISR _CMPInterrupt();
void tv_vsync();
void tv_csync();

#endif	// OSD_H
