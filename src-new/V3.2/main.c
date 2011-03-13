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

#include <p33fj128gp802.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "useful.h"
#include "console.h"
#include "interface.h"
#include "fonts.h"
#include "gfx.h"
#include "osd.h"

extern uint16_t *draw_buffer_level;
extern uint16_t *draw_buffer_mask;
extern uint16_t *disp_buffer_level;
extern uint16_t *disp_buffer_mask;

/* Configuration bits. */
// Fast RC oscillator with divide & PLL, two-speed oscillator startup disabled
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF);
// No clock monitor/failsafe, remappable I/O, clock out enabled, primary oscillator disabled.
_FOSC(FCKSM_CSDCMD & IOL1WAY_ON & OSCIOFNC_OFF & POSCMD_NONE);
// Watchdog enabled.
_FWDT(FWDTEN_OFF);
// JTAG off, ICD using PGD1/PGC1.
_FICD(JTAGEN_OFF & ICS_PGD1);
// Primary I2C.
//_FPOR(~ALTI2C);

int main()
{
	long int delay;
	int brg;
	char temp[50];
	// Call the various initialization functions.
	init_osd();
	setup_pll();
 	setup_io();
 	setup_int();
	init_gfx(1);
	// Turn on doze, with a 1:1 ratio.
	CLKDIVbits.DOZEN = 0;
	CLKDIVbits.DOZE = 0b000;
	// Start in console mode. Print startup messages.
	con_init();
	con_rolling = 0;
	con_puts("Super OSD v3.2-lite", 0);
	con_puts("dsPIC33F side", 0);
	con_puts("Copr. 2010 Tom O.", 0); ;
	con_puts("COMPILED FOR: ENGLISH", 0);
	con_puts("", 0); 
	con_puts("Booting kernel    [ OK ]", 0);
	con_puts("Verify 24F        [ OK ]", 0);
	con_puts("Verify 33F        [ OK ]", 0);
	con_puts("Switch to hi res  [ OK ]", 0);
	init_gfx(0);
	if(mem_test_full())
	{
		con_puts("VRAM test         [ OK ]", 0);
	}
	else
	{
		con_puts("VRAM test         [FAIL]", 0);
		con_puts("Check memory soon!      ", 0);
		// Show warning for some time
		delay = 2000000;
		while(delay--); 
	}
	// Clear graphics buffers of any memory test data remaining.
	init_gfx(0);
	con_puts("Init UART         [ OK ]", 0);
	// BUG: occasionally resets processor on start up
	//interface_init_uart();
	//brg = interface_set_baudrate(1843200);
	//sprintf(temp, "BRG=%d", brg);
	//con_puts(temp, 0);
	/*
	con_puts("PC detect...      [FAIL]", 0);
	con_puts("GPS detect...     [ OK ]", 0);
	con_puts("SPI initialized   [ OK ]", 0);
	con_puts("Found flash mem   [ OK ]", 0);
	con_puts("  Size: 2048 KB   [ OK ]", 0);
	con_puts("USB not supported [SKIP]", 0);
	con_puts("Init GPS          [ OK ]", 0);
	con_puts("Test I2C          [ OK ]", 0);
	con_puts("  Xbee Adap. 2.0  [ OK ]", 0);
	con_puts("  LSM303 acc      [ OK ]", 0);
	con_puts("  LSM303 mag      [ OK ]", 0);
	con_puts("  ITG3200 gyro    [FAIL]", 0);
	con_puts("Loading settings  [ OK ]", 0);
	con_puts("Init splash       [ OK ]", 0);
	*/	
	// Demo HUD.
	//buffer_mode(0);
	con_puts("Launching hud_demo", 0);
	hud_demo();
}
