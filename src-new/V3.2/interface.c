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

/*
 * This code handles the external interface, including I2C, and
 * parsing commands and sending the commands off to the various
 * drawing functions. The code is mixed with the OSD code, which
 * captures some of the I2C data.
 */

char cmd_buffer[CMD_BUFFER_SIZE];
int cmd_buffer_ptr;
int cmd_buffer_full;

/**
 * interface_init: Initialize the I2C interface and command 
 * buffers. This should be called before the first TV line
 * interrupt, or line interrupts should be disabled while it
 * is processing, otherwise commands may be lost.
 */
void interface_init_i2c()
{
	int i = 0;
	while(i < CMD_BUFFER_SIZE)
	{
		cmd_buffer[i] = 0x00;
		i++;
	}
	cmd_buffer_full = 0;
	cmd_buffer_ptr = 0;
	// Setup I2C as a slave device.
	I2C1CONbits.I2CEN = 0; 		// initially disable it
	I2C1CONbits.I2CSIDL = 0;	// don't stop in idle mode
	I2C1CONbits.SCLREL = 1;		// turn off clock stretching
	I2C1CONbits.IPMIEN = 0;		// IPMIEM support off
	I2C1CONbits.A10M = 0;		// use 7-bit addresses
	I2C1CONbits.DISSLW = 1;		// disable slew rate control
	I2C1CONbits.SMEN = 0;		// SMBus compatibility off
	I2C1CONbits.GCEN = 0;		// ignore general call
	I2C1CONbits.STREN = 1;		// allow for clock stretching to be used
	I2C1ADD = I2C_MY_ADDR;		// set address
	I2C1MSK = 0x00;				// no masking
	I2C1RCV = 0x00;				// clear receive buffer
	I2C1TRN = 0x00;				// clear transmit buffer
	I2C1BRG = 0xffff;			// BRG not important as we are a slave and not a master
	I2C1CONbits.I2CEN = 0; 		// now enable I2C1.
}

/**
 * interface_handle_i2c: Handle the I2C buffer. Called on each
 * TV CSYNC line and occasionally in the main loop.
 */
void interface_handle_i2c()
{
	// I2C buffer is full. Is receive buffer full?
	// If so, put byte into the command buffer.
	if(I2C1STATbits.RBF && !cmd_buffer_full)
		cmd_buffer[cmd_buffer_ptr++] = I2C1RCV;
	// If STOP (bit P) has been asserted, or, if the command buffer 
	// has overflowed. then it is the end of any given command, so 
	// end the buffer. This signals to the main application code that 
	// the buffer must be handled.
	if(I2C1STATbits.P || cmd_buffer_ptr >= CMD_BUFFER_SIZE - 1)
	{
		// The following should be atomic. How do we ensure this?
		cmd_buffer_full = 1;
		I2C1CONbits.SCLREL = 0; // clock stretching on
	}
	// Are we okay now to accept another byte?
	if(cmd_buffer_full == 0)
		I2C1CONbits.SCLREL = 1; // clock stretching off
}

/**
 * interface_handle_command: Handle the command buffer. After
 * this, the buffer is marked as empty and the pointer is reset.
 * It is important for that operation to be atomic, so a single
 * bit is set to indicate the buffer is to be reset and this
 * is handled on each CSYNC line. Otherwise, an interrupt between
 * the write to the full bit and the pointer could cause the
 * command buffer to be clobbered.
 */
void interface_handle_command()
{
	// Argument temporaries.
	int x0 = 0, y0 = 0, x1 = 0, y1 = 0;
	int ec0 = 0, ec1 = 0;
	int i = 0;
	char cksum = 0x00;
	// Check the command arrived correctly using the checksum.
	// The checksum is very basic, but handles simple bit errors, which is
	// pretty much the only thing that can happen with I2C.
	while(i < cmd_buffer_ptr) // up to the last byte
		cksum ^= cmd_buffer[i++];
	// In future, handle errors more gracefully.
	MY_ASSERT(cksum == cmd_buffer[cmd_buffer_ptr]);
	// First byte indicates type of command.
	switch(cmd_buffer[0])
	{
		case 0x00: break; // NOP/ping
		// Draw outlined horizontal line.
		// Expects arguments: x0, y0, x1, y1, ec0, ec1, mode, mmode (11 bytes.)
		case 0x01: 
			x0 = EXTRACT_INT16(cmd_buffer, 1);
			y0 = EXTRACT_INT16(cmd_buffer, 3);
			x1 = EXTRACT_INT16(cmd_buffer, 5);
			y1 = EXTRACT_INT16(cmd_buffer, 7);
			ec0 = cmd_buffer[8];
			ec1 = cmd_buffer[9];
			mode = cmd_buffer[10];
			mmode = cmd_buffer[11];
			write_hline_outlined(x0, y0, x1, y1, ec0, ec1, mode, mmode);
			break;
	}
}
