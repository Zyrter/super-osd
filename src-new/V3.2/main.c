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
#include "useful.h"
#include "interface.h"
#include "fonts.h"
#include "gfx.h"
#include "osd.h"

/* Configuration bits. */
// Fast RC oscillator with divide & PLL, two-speed oscillator startup disabled
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF);
// No clock monitor/failsafe, remappable I/O, clock out enabled, primary oscillator disabled.
_FOSC(FCKSM_CSDCMD & IOL1WAY_ON & OSCIOFNC_OFF & POSCMD_NONE);
// Watchdog enabled.
_FWDT(FWDTEN_OFF);
// JTAG off, ICD using PGD1/PGC1.
_FICD(JTAGEN_OFF & ICS_PGD1);

int main()
{
	// Call the various initialization functions.
	init_osd();
	setup_pll();
 	setup_io();
 	interface_init_i2c();
 	setup_int();
	init_gfx();
	// Start in console mode.
	con_init();
	con_puts("Super OSD v3.2-lite");
	con_puts("Copr. 2010 Tom O."); 
	con_puts("This is GPLv2 software"); 
	con_puts("Launching demo_game");
	// Load demo game.
	demo_game();
}