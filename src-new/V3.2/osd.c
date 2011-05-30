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

#include <stdlib.h>

#include "gfx.h"
#include "osd.h"
#include "interface.h"

#define  PPS_UNLOCK		__builtin_write_OSCCONL(OSCCON & 0xbf)
#define  PPS_LOCK		__builtin_write_OSCCONL(OSCCON | 0x40) 

#include <p33fj128gp802.h>

char tv_format, tv_tent_format; // FORMAT_PAL or FORMAT_NTSC.
char have_vsync, field_odd, tv_format_switch;
unsigned int tv_line, tv_field, tv_gfx_y, tv_max_line, tv_tent_format_count, tv_real_line;
long int tv_time;
int vsync_last, timer2_dc, timer2_osd;
int vid_hoffset, vid_voffset;

// scanlines are 32 bytes each (16 words; enough for 256 pixels horizontal resolution.)
uint16_t scanline_mask[16];
uint16_t scanline_level[16];
uint16_t scanline_mask_out[16];
uint16_t scanline_level_out[16];

int audio_l_tmaster, audio_l_tmask;
int audio_r_tmaster, audio_r_tmask;

#define AUDIO_FREQ(f) (31250 / f) // this is not quite true for NTSC, but it is close enough

// Assembly output routines.
extern int osd_out_lores(short *ptr_set_clear, short *ptr_black_white, short num_words); 
extern int osd_out_hires(short *ptr_set_clear, short *ptr_black_white, short num_words); 

/**
 * The OSD files handle the actual output of the graphics framebuffer
 * as an overlay on the video signal.
 */

/**
 * init_osd: clear/initialize vars.
 */
void init_osd()
{
	int i;
	vid_hoffset = 0;
	vid_voffset = 0;
	tv_time = 0;
	tv_line = 0;
	tv_field = 0;
	field_odd = 0;
	tv_format = FORMAT_PAL; // default PAL
	have_vsync = 0;
	// Initialize L audio output for 3kHz audio output, with a 10Hz gate signal.
	audio_l_tmaster = AUDIO_FREQ(3000);
	audio_l_tmask = AUDIO_FREQ(10);
	// Initialize L audio output for 2kHz audio output continuously.
	audio_l_tmaster = AUDIO_FREQ(2000);
	audio_l_tmask = 0;
}

/**
 * prep_scanline: Prepare scanline; rotate each word 6 times left and
 * for the mask scanline, invert it.
 */
void prep_scanline(uint16_t *scanline_in, uint16_t *scanline_out, int is_mask, int words)
{
	//asm("bclr SR, #0");
	int i = 0, mask = 0;
	if(is_mask) mask = 0xffff;
	while(words--)
	{
		uint16_t word = scanline_in[i];
		word = (word << 5) | (word >> 11); // Fast 5-way rotate for 16-bit word
		word ^= mask; // quick way of inverting on demand
		//scanline_out[i] = 0x5555;
		scanline_out[i] = word;
		i++;
	}
	/*
	while(words--)
	{
		// Probably a more optimal way of doing this, but it works. 
		uint16_t word = scanline_in[i];
		asm("rlnc %0, %0" : "+r"(word));
		asm("rlnc %0, %0" : "+r"(word));
		asm("rlnc %0, %0" : "+r"(word));
		asm("rlnc %0, %0" : "+r"(word));
		asm("rlnc %0, %0" : "+r"(word));
		word ^= mask; // quick way of inverting on demand
		scanline_out[i] = word;
		i++;
	}
	*/
}

/**
 * setup_pll: Set up the internal oscillator and PLL, so we run at 
 * approximately 36.85 MHz, a baud multiple (important for board 
 * level communications.)
 */
void setup_pll()
{
	// Disable interrupts (must be done during speed changes.)
	SRbits.IPL = 0;
	// We want an Fcy of 36.85 MHz from a 7.37 MHz (FRC) input.
	// To do this we need to divide the input by two.
	CLKDIVbits.PLLPRE = 0; // N1=2; Fref 3.685 MHz.
	// Then we want to multiply by 40 to give an Fvco of 147.4 MHz.
	// The Fvco output must be in the range of 100 - 200 MHz.
	PLLFBD = 39; // M=40
	// Then we want to divide the Fvco by 2 to give 73.7 MHz (which gives
	// us an Fcy of 36.85 MHz.)
	CLKDIVbits.PLLPOST = 0b00; // N2=2
	// Wait for PLL to lock.
	while(OSCCONbits.LOCK != 1) ;
	// Enable interrupts again.
	SRbits.IPL = 7;
}

/**
 * setup_io: Initialize input and output stuff.
 */
void setup_io()
{
	// Set video output as an input (for now.)
	TRISBbits.TRISB5 = 1;
	// Setup CSYNC, VSYNC, ODDEVEN inputs.
	TRISBbits.TRISB6 = 1;
	TRISBbits.TRISB7 = 1;
	TRISBbits.TRISB10 = 1;
	// Set debugging pins as outputs.
	TRISBbits.TRISB15 = 0;	// Comparator gone positive
	TRISBbits.TRISB14 = 0;	// Vertical sync
	TRISBbits.TRISB13 = 0;	// Line output
	// Setup on-chip DAC.
	//DAC1CONbits.DACEN = 1;
	//DAC1CONbits.DACSIDL = 0;
	//DAC1CONbits.AMPON = 1;
	//DAC1CONbits.FORM = 0;
	//DAC1CONbits.DACFDIV = 8;
	//DAC1STATbits.LOEN = 1;
	//DAC1DFLT = 0x0000;
}

/**
 * setup_int: Setup interrupts and turn them on.
 */
void setup_int()
{
	// Set up clock recover on interrupt, which disables doze for interrupts.
	CLKDIVbits.ROI = 0;
	// Set up pin change notification interrupt on CN24.
	CNEN2bits.CN24IE = 1;
	IPC4bits.CNIP = 4;
	IFS1bits.CNIF = 0;
	IEC1bits.CNIE = 1;
	// Initialize Timer1, which is used for pulse width measurement.
	T1CONbits.TON = 0;
	T1CONbits.TSIDL = 0;	// TODO: sleep modes - this is the stop in idle bit
	T1CONbits.TCKPS = 0;
	T1CONbits.TCS = 0;
	T2CONbits.TON = 1;
	// Initialize Timer2, which is used for output timing.
	T2CONbits.TON = 0;
	T2CONbits.TSIDL = 0;
	T2CONbits.TCKPS = 0;
	T2CONbits.TCS = 0;
	T2CONbits.T32 = 0;
	T2CONbits.TON = 1;
	// Initialize Timer2 interrupt with a slightly
	// higher priority.
	IPC1bits.T2IP = 5;
	IFS0bits.T2IF = 0;
	IEC0bits.T2IE = 0;
	// Enable interrupts and set CPU priority (to zero.)
	SET_CPU_IPL(0);
}

/**
 * disable_int: Disable interrupts.
 */
void disable_int()
{
	// Turn off timers.
	T1CONbits.TON = 0;
	T2CONbits.TON = 0;
	// Interrupts are disabled by making the CPU's priority highest.
	SET_CPU_IPL(7);
}

/**
 * _CNInterrupt: Primary ISR for pin change interrupts.
 */ 
void _MY_ISR _CNInterrupt()
{
	// Enable Timer2.
	if(tv_format == FORMAT_PAL)
		timer2_osd = 420 + vid_hoffset;
	else if(tv_format == FORMAT_NTSC)
		timer2_osd = 350 + vid_hoffset;
	T2CONbits.TON = 1;
	TMR2 = 0;
	// Check if VSYNC is high OR, if it is low, that the last line
	// wasn't a falling edge.
	if(PORTBbits.RB7 == 1 || vsync_last == 0)
	{
		tv_csync(); // handle CSYNC
		tv_line += 2; // add 2 to compensate for interlace
		tv_real_line++;
	}
	// Signal VSYNC refresh on each frame (not each field!)
	if(tv_field % 2 == 0)
		have_vsync_refresh = 1;
	// If the VSYNC pin is low, determine if this was a falling
	// edge or not. If so, this is a VSYNC event and needs to be
	// handled appropriately.
	if(PORTBbits.RB7 == 0 && vsync_last == 1)
	{
		tv_vsync();
		//vid_hoffset += 1;
		//if(vid_hoffset > 80) vid_hoffset = -80;
	}
	vsync_last = PORTBbits.RB7;
	IFS1bits.CNIF = 0;
	// Switch off Timer2.
	T2CONbits.TON = 0;
	TMR2 = 0;
	// Enable DOZE again (could be 1:1.)
	CLKDIVbits.DOZEN = 0;
}

/**
/ * tv_vsync: VSYNC handler. This fires on each field 50 
 * or 60 times per second.
 */
void tv_vsync()
{
	// How many lines in the last field?
	// What we want to do is count the number of lines to determine
	// the video format. If after more than 200 fields we have detected
	// a different format, then we need to switch.
	
	// Why so big? These are the measured values! Plus/minus a bit of error.
	// Not entirely sure what causes these to be so out. But it seems to work...?
	// PAL
	if(tv_real_line > 400 && tv_real_line < 420)
	{
		if(tv_format != FORMAT_PAL)
		{
			if(tv_tent_format != FORMAT_PAL) tv_tent_format_count = 0;
			tv_tent_format = FORMAT_PAL;
			tv_tent_format_count++;
		}
	}
	// NTSC
	else if(tv_real_line > 300 && tv_real_line < 320)
	{
		if(tv_format != FORMAT_NTSC)
		{
			if(tv_tent_format != FORMAT_NTSC) tv_tent_format_count = 0;
			tv_tent_format = FORMAT_NTSC;
			tv_tent_format_count++;
		}
	}
	// Switch format?
	if(tv_tent_format_count > 200)
	{
		tv_format = tv_tent_format;
		tv_format_switch = 1; // code must clear this
	}
	tv_max_line = tv_real_line;
	tv_real_line = 0;
	if(PORTBbits.RB10 == 1) // field is odd; start at 1.
		tv_line = 1;
	else					// field is even; start at 0.
		tv_line = 0;
	tv_field++;
	// If the field counter has reached 50 for PAL or 60 for
	// NTSC, reset it and start it at zero, then count a second.
	if((tv_field == 50 && tv_format == FORMAT_PAL) || (tv_field == 60 && tv_format == FORMAT_NTSC))
	{
		tv_field = 0;
		tv_time++;
	}
	// Notify vsync'd code that we have vsync.
	have_vsync_refresh = 1;
}

/**
 * tv_csync: CSYNC handler. This fires on each line at ~30 kHz.
 * 
 * Please note a lot of the numbers in this are from trial and 
 * error. These should be replaced with constants in future.
 */
void tv_csync()
{
	int icomp = 1, interlace_offset = 0;
	if(tv_line < 45)
		return;
	// Compensate for interlacing artefacts.
	if(PORTBbits.RB10 == 0) 
		icomp = 0;
	// Compute the GFX Y position and hence the address.
	if(disp_mode == 1)
	{
		if((tv_format == FORMAT_PAL && tv_line > 480) || (tv_format == FORMAT_NTSC && tv_line > 325))
			return;
		if(tv_format == FORMAT_PAL)
			tv_gfx_y = ((long int)(tv_line + icomp + vid_voffset - 50) * PAL_GFX_SCALE_192) / 256;
		else
			tv_gfx_y = ((long int)(tv_line + icomp + vid_voffset - 50) * NTSC_GFX_SCALE_192) / 256;
	}
	else if(disp_mode == 0)
	{
		if(tv_format == FORMAT_PAL)
			tv_gfx_y = (tv_line + vid_voffset - 230) / 2; 
		else if(tv_format == FORMAT_NTSC)
			tv_gfx_y = (tv_line + vid_voffset - 230) / 2; 
	}
	// Exit if GFX Y too big.
	if(tv_gfx_y > disp_height)
		return;
	int addr = tv_gfx_y * (disp_width / 16);
	// Prepare the scanline. We are time constrained, so the below must be FAST!
	prep_scanline(disp_buffer_mask + addr, scanline_mask_out, 1, disp_width / 16);
	prep_scanline(disp_buffer_level + addr, scanline_level_out, 0, disp_width / 16);
	// Wait for OSD time. (TODO: Execute other code in this time? Consider timer period match interrupt...)
	while(TMR2 <= timer2_osd);
	// Output screen data.
	TRISBbits.TRISB5 = 1; // tristate before sending
	if(disp_mode == 1)
		osd_out_lores(scanline_mask_out, scanline_level_out, disp_width / 16);
	else if(disp_mode == 0)
		osd_out_hires(scanline_mask_out, scanline_level_out, disp_width / 16);
	// Tristate output so as not to cause problems.
	TRISBbits.TRISB5 = 1;
	IFS0bits.T2IF = 0;
	return;
}
