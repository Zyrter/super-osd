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

#include "osd.h"
#include "console.h"

/*
 * These files manage the virtual console. The console is used for 
 * debugging and on startup. The functions are similar to old DOS 
 * APIs.
 */
// TODO/FIXME: assumes 8x8 characters
struct ConChar cons[DISP_WIDTH / 8][DISP_HEIGHT / 8];
const int con_width = DISP_WIDTH / 8;
const int con_height = DISP_HEIGHT / 8;
struct ConCurs curs;

/**
 * con_init: Initialize the console.
 */
void con_init()
{
	unsigned char ch;
	int x, y;
	// Initialize cursor.
	curs.x = 0;
	curs.y = 0;
	// Demo/test console on startup.
	con_fillscr(0, 0);
	con_puts("Console init", 0);
	for(y = 0; y < con_height; y++)
	{
		for(x = 0; x < con_width; x++)
		{
			con_setchr(x, y, x + (y * con_width), 0);
		}
	}
	con_flush();
	con_fillscr(' ', 0);
	// Reset cursor.
	curs.x = 0;
	curs.y = 0;
	con_flush();
}

/**
 * con_setchr: Set a character at a location without
 * incrementing or moving the console cursor.
 */
void con_setchr(int x, int y, char ch, char attr)
{
	cons[x][y].ch = ch;
	cons[x][y].attr = attr;
	//con_flush();
}

/**
 * con_scrollup: Move the console one line up.
 */
void con_scrollup()
{
	int x, y;
	// Delete the topmost row.
	for(x = 0; x < con_width; x++)
		con_setchr(x, 0, ' ', 0);
	// Copy each row.
	for(y = 1; y < con_height; y++)
	{
		for(x = 0; x < con_width; x++)
		{
			con_setchr(x, y - 1, cons[x][y].ch, cons[x][y].attr);
		}
	}
	// Delete the bottom row.
	for(x = 0; x < con_width; x++)
		con_setchr(x, con_height - 1, ' ', 0);
}

/**
 * con_fillscr: Fill screen with a character.
 *
 * @param	ch		character to write
 * @param	attr	attributes for character
 */
void con_fillscr(char ch, char attr)
{
	int x, y;
	for(x = 0; x < con_width; x++)
	{
		for(y = 0; y < con_height; y++)
		{
			con_setchr(x, y, ch, attr);
		}
	}
	con_flush();
}

/**
 * con_clrscr: Clear the screen.
 */
void con_clrscr()
{
	con_fillscr(' ', 0);
}

/**
 * con_putchr: Place a character and increment the cursor.
 *
 * @param	ch		character to be written
 * @param	attr	attributes for character
 */
void con_putchr(char ch, char attr)
{
	if(ch == '\n' || ch == '\r')
	{
		// New line.
		curs.y++;
		curs.x = 0;
	}
	else if(ch == '\v')
	{
		// Vertical tab: y increments, x stays the same.
		curs.y++;
	}
	else if(ch == '\t')
	{
		// Horizontal tab support TODO.
	}
	else
	{
		if(curs.x > con_width - 1)
		{
			curs.x = 0;
			curs.y++;
		}
		con_setchr(curs.x, curs.y, ch, attr);
		curs.x++;
	}
	// If y exceeds bounds, scroll up the window.
	if(curs.y > con_width - 1)
	{
		con_scrollup();
		con_flush();
		curs.y--;
	}
}

/**
 * con_puts: Write a string to the console. Newline is
 * automatically added.
 */
void con_puts(char *s, char attr)
{
	while(*s != '\0')
	{
		con_putchr(*s, attr);
		s++;
	}
	con_putchr('\n', 0);
	con_flush();
}

/**
 * con_flush: Update the display to reflect the current
 * console buffer.
 */
void con_flush()
{
	int x, y;
	// Clear the graphics framebuffers.
	fill_buffer(draw_buffer_mask, 0x0000);
	fill_buffer(draw_buffer_level, 0xffff);
	// Update the framebuffers.
	for(x = 0; x < con_width; x++)
	{
		for(y = 0; y < con_height; y++)
		{
			// Write the character on the display.
			// TODO: handle attributes.
			write_char(cons[x][y].ch, x * 8, y * 8, 0, 1);
		}
	}
	// Switch buffers.
	swap_buffers();
}