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

#ifndef INTERFACE_H
#define INTERFACE_H

#define UART_BUFFSZ		256

// Function prototypes.
void interface_init_uart();
unsigned int interface_set_baudrate(long int baudrate);

#endif // INTERFACE_H