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

#include "gfx.h"
#include "osd.h"
#include <stdlib.h>

#define  PPS_UNLOCK		__builtin_write_OSCCONL(OSCCON & 0xbf)
#define  PPS_LOCK		__builtin_write_OSCCONL(OSCCON | 0x40) 

#include <p33fj128gp802.h>

char tv_format, have_vsync; // FORMAT_PAL or FORMAT_NTSC.
unsigned int tv_line, tv_field, tv_gfx_y;
long int tv_time;
int vsync_last, timer2_dc, timer2_osd;
int vid_hoffset, vid_voffset;

uint16_t scanline_mask[DISP_WIDTH / 16];
uint16_t scanline_level[DISP_WIDTH / 16];
uint16_t scanline_mask_out[DISP_WIDTH / 16];
uint16_t scanline_level_out[DISP_WIDTH / 16];

int audio_l_tmaster, audio_l_tmask;
int audio_r_tmaster, audio_r_tmask;

#define AUDIO_FREQ(f) (31250 / f) // this is not quite true for NTSC, but it is close enough

/* Assembly output. */
extern int osd_out(short *ptr_set_clear, short *ptr_black_white, short num_words); 

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
	vid_voffset = 1;
	tv_time = 0;
	tv_line = 0;
	tv_field = 0;
	tv_format = FORMAT_PAL; // default PAL
	have_vsync = 0;
	// Initialize L audio output for 3kHz audio output, with 
	// a 10Hz gate signal.
	audio_l_tmaster = AUDIO_FREQ(3000);
	audio_l_tmask = AUDIO_FREQ(10);
	// Initialize L audio output for 2kHz audio output continuously.
	audio_l_tmaster = AUDIO_FREQ(2000);
	audio_l_tmask = 0;
	// Initialize scanlines with something interesting.
	scanline_mask[0] = 0xcccc;
	scanline_level[0] = 0x0000;
	scanline_mask[1] = 0xcccc;
	scanline_level[1] = 0xffff;
	scanline_mask[2] = 0xffff;
	scanline_level[2] = 0x5555;
	scanline_mask[3] = 0xffff;
	scanline_level[3] = 0xffff;
	scanline_mask[4] = 0xffff;
	scanline_level[4] = 0x0000;
	scanline_mask[5] = 0xcccc;
	scanline_level[5] = 0x0000;
	scanline_mask[6] = 0xffff;
	scanline_level[6] = 0x00ff;
	scanline_mask[7] = 0x5555;
	scanline_level[7] = 0x00ff;
	scanline_mask[9] = 0x073C;  // test line
	scanline_level[9] = 0x0218; // test line
}

/**
 * prep_scanline: Prepare scanline; rotate each word 6 times left and
 * for the mask scanline, invert it.
 */
void prep_scanline(uint16_t *scanline_in, uint16_t *scanline_out, int is_mask, int words)
{
	asm("bclr SR, #0");
	int i = 0, mask = 0;
	if(is_mask) mask = 0xffff;
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
}

/**
 * setup_pll: Set up the internal oscillator and PLL, so we run at 
 * approximately 40 MIPS.
 *
 * The actual speed with these settings is 42 MIPS +/- 0.4 MIPS,
 * which although slightly out of spec (40 MIPS) it should be okay.
 */
void setup_pll()
{
	// Disable interrupts (must be done during speed changes.)
	SRbits.IPL = 0;
	// These values seem to work well.
	PLLFBD = 155; // or 154
	CLKDIVbits.PLLPRE = 5;
	CLKDIVbits.PLLPOST = 0;
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
	DAC1CONbits.DACEN = 1;
	DAC1CONbits.DACSIDL = 0;
	DAC1CONbits.AMPON = 1;
	DAC1CONbits.FORM = 0;
	DAC1CONbits.DACFDIV = 8;
	DAC1STATbits.LOEN = 1;
	DAC1DFLT = 0x0000;
}

/**
 * setup_int: Setup interrupts and turn them on.
 */
void setup_int()
{
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
 * Disable interrupts.
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
 * Primary ISR for pin change interrupts.
 */ 
void _MY_ISR _CNInterrupt()
{
	// Enable Timer2.
	timer2_osd = 550 + vid_hoffset;
	T2CONbits.TON = 1;
	TMR2 = 0;
	// Handle I2C.
	interface_handle_i2c();
	// Output a debugging pulse.
	//PORTBbits.RB15 = 1;
	//PORTBbits.RB15 = 0;
	// Check if VSYNC is high OR, if it is low, that the last line
	// wasn't a falling edge..
	if(PORTBbits.RB7 == 1 || vsync_last == 0)
	{
		tv_csync(); // handle CSYNC
		tv_line++;
	}
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
}

/**
 * tv_vsync: VSYNC handler. This fires on each field 50 
 * or 60 times per second.
 */
void tv_vsync()
{
	// How many lines in the last field?
	// There are 288 lines in PAL, and 240 in NTSC, per field. 
	// Give some leeway (+/-8%) for counting errors or uncounted 
	// pulses. Use this to determine the video format.
	// Sometimes the video format is incorrectly detected as NTSC,
	// instead of PAL. This needs to be fixed.
	if(tv_line > 264 && tv_line < 330)
		tv_format = FORMAT_PAL; // also works for SECAM(?)
	/* ain't workin'
	else if(tv_line > 220 && tv_line < 259) 
		tv_format = FORMAT_NTSC;  
	*/
	else {} // else, don't change format.
	tv_line = 1;
	tv_field++;
	// If the field counter has reached 50 for PAL or 60 for
	// NTSC, reset it and start it at zero, then count a second.
	if((tv_field == 50 && tv_format == FORMAT_PAL) || (tv_field == 60 && tv_format == FORMAT_NTSC))
	{
		tv_field = 0;
		tv_time++;
	}
}

/**
 * tv_csync: CSYNC handler. This fires on each line at ~30 kHz.
 * 
 * Please note a lot of the numbers in this are from trial and 
 * error. These should be replaced with constants in future.
 */
void tv_csync()
{
	int icomp = 0;
	if(tv_line < 45)
		return;
	if((tv_format == FORMAT_PAL && tv_line > 330) || (tv_format == FORMAT_NTSC && tv_line > 325))
		return;
	// Compensate for interlacing artefacts.
	if(PORTBbits.RB10 == 0) 
		icomp = 1;
	// Compute the GFX Y position and hence the address.
	if(tv_format == FORMAT_PAL)
		tv_gfx_y = ((long int)(tv_line + icomp + vid_voffset - 50) * PAL_GFX_SCALE) / 64;
	else
		tv_gfx_y = ((long int)(tv_line + icomp + vid_voffset - 50) * NTSC_GFX_SCALE) / 64;
	int addr = tv_gfx_y * (DISP_WIDTH / 16);
	// Prepare the scanline. We are time constrained, so just copy the pointers
	// from the graphics memory to the scanline pointers.
	prep_scanline(disp_buffer_mask + addr, scanline_mask_out, 1, DISP_WIDTH / 16);
	prep_scanline(disp_buffer_level + addr, scanline_level_out, 0, DISP_WIDTH / 16);
	// Wait for OSD time. (TODO: execute other code in this time.)
	while(TMR2 <= timer2_osd);
	// Output screen data.
	TRISBbits.TRISB5 = 1; // tristate before sending
	osd_out(scanline_mask_out, scanline_level_out, DISP_WIDTH / 16);
	// Tristate output so as not to cause problems.
	TRISBbits.TRISB5 = 1;
	IFS0bits.T2IF = 0;
	return;
}