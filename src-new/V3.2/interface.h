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

/*
 * This code handles the external interface, including I2C, and
 * parsing commands and sending the commands off to the various
 * drawing functions. The code is mixed with the OSD code, which
 * captures some of the I2C data.
 */

#define CMD_BUFFER_SIZE	128		// 128 bytes buffer
#define I2C_MY_ADDR		0x32	// default I2C address: 0x32

#define EXTRACT_INT16(buff, p) (buff[p] | buff[(p) + 1] << 8)

// Buffer definitions.
extern char cmd_buffer[CMD_BUFFER_SIZE];
extern int cmd_buffer_ptr;
extern int cmd_buffer_full;

// Function prototypes.
void interface_init_i2c();
void interface_handle_i2c();
