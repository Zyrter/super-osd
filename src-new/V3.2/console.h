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
 * These files manage the virtual console. The console is used for 
 * debugging and on startup. The functions are similar to old DOS 
 * APIs.
 */

#define CON_ATTR_INVERT		1
#define CON_ATTR_BLINK		2
#define CON_ATTR_HIGHLIGHT	4

typedef struct ConChar { char ch, attr; };
typedef struct ConCurs { int x, y; };

// Function prototypes.
void con_init();
void con_scrollup();
void con_fillscr(char ch, char attr);
void con_clrscr();
void con_setchr(int x, int y, char ch, char attr);
void con_putchr(char ch, char attr);
void con_puts(char *str, char attr);
void con_printf(char *fmt, char attr, ...);
void con_curhome();
void con_curset(int x, int y);
void con_flush();