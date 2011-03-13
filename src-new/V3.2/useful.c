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

#include "useful.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char temp_buff[100];

/**
 * panic: fatal error routine. Panic displays the message
 * on the screen, then waits 2 seconds before restarting
 * the processor.
 *
 * @param	message to print
 */
void panic(char *msg)
{
	long int d = 5000000;
	// Initialize console, print message.
	con_init();
	con_puts("PANIC ON OSD DSP !!");
	con_puts("Super OSD's on screen display processor encountered a fatal error condition.");
	con_puts("");
	con_puts(msg);
	con_puts("");
	con_puts("Resetting soon.");
	// Reset after timer expires.
	while(d--);
	asm("reset");
}

/**
 * safe_malloc: allocate memory or jump to an error routine.
 *
 * @param	size of memory to be allocated
 */
void *safe_malloc(size_t size)
{
	void *ptr = malloc(size);
	if(ptr == NULL)
	{
		sprintf(temp_buff, "malloc of %u (0x%x) bytes failed", (unsigned int)size, (unsigned int)size);
		panic(temp_buff);
	}
	return ptr;
}

/**
 * safe_calloc: "calloc" memory or jump to an error routine.
 *
 * @param	num elements
 * @param	size of each element
 */
void *safe_calloc(size_t num, size_t size)
{
	void *ptr = calloc(num, size);
	if(ptr == NULL)
	{
		sprintf(temp_buff, "calloc of %u (0x%x) bytes failed", (unsigned int)size, (unsigned int)size);
		panic(temp_buff);
	}
	return ptr;
}

/**
 * safe_realloc: "realloc" memory or jump to an error routine.
 *
 * @param	former pointer
 * @param	new size
 */
void *safe_realloc(void *ptr, size_t size)
{
	void *newptr = realloc(ptr, size);
	if(newptr == NULL)
	{
		sprintf(temp_buff, "realloc of %u (0x%x) bytes failed (oldptr=%x)", (unsigned int)size, (unsigned int)size, (unsigned int)(&ptr));
		panic(temp_buff);
	}
	return newptr;
}

/**
 * Implementations of itoa and reverse.
 * http://en.wikipedia.org/wiki/Itoa
 */
/**
 * my_itoa: convert n to characters in s. This version is slightly
 * modified; it returns the number of bytes (including NUL) written.
 *
 * @param	number (long int)
 * @param	string buffer
 *
 * @return 	Bytes written
 */
int my_itoa(long int n, char s[])
{
	long int i, sign;
	if ((sign = n) < 0)	            /* record sign */
		n = -n;				        /* make n positive */
	i = 0;
	do                              /* generate digits in reverse order */
	{	   
		s[i++] = n % 10 + '0';      /* get next digit */
	} while ((n /= 10) > 0);	    /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	my_reverse(s);
	return i + 1;
}

/**
 * reverse: reverse string s in place
 *
 * @param	string buffer
 */
void my_reverse(char s[])
{
	int i, j;
	char c;
	for (i = 0, j = strlen(s) - 1; i<j; i++, j--) 
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/**
 * intpow: Raise number to integer power. Takes the slow
 * route of iterative multiplication.
 *
 * @param	x
 * @param	y
 */
long int intpow(int x, int y)
{
	long int r = x;
	if(y == 0) 
		return 1;
	if(y == 1) 
		return x;
	if(y < 0)
		return 0; // negative powers not supported.
	while(y--) 
		r *= x;
	return r;
}

/**
 * fpllstring: Floating point lat/lon to string.
 */
void fpllstring(float ll, int digits, char *s)
{
	long int ipart = ll;
	long int fpart = fabs((ll - ipart) * intpow(10, digits - 1));
	my_itoa(ipart, s);
	strcat(s, ".");
	my_itoa(fpart, temp_buff);
	// pad out if less than 10^d.
	int pad = digits - strlen(temp_buff);
	while(pad > 0)
	{
		strcat(s, "0");
		pad--;
	}
	strcat(s, temp_buff);
}
