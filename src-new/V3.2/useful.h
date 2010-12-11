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

#ifndef USEFUL_H
#define USEFUL_H

#include <stdlib.h>

// Assert routine.
#define MY_ASSERT(x) { if(!(x)) panic("assert failed: " #x); }

/*
 * Useful extra features, like size of array, convert degrees to radians...
 */

// Macros for degree/radian conversion.
#define DEG2RAD(x)	((x) * 0.0174532925f)
#define RAD2DEG(x)	((x) * 57.2957795f)

// Size of an array (num items.)
#define SIZEOF_ARRAY(x) (sizeof(x) / sizeof((x)[0]))

// Useful constants. 
#define CONST_2PI	6.283185307f
#define CONST_PI	3.1415926535f

// Max/Min macros.
#define MAX(a, b)		((a) > (b) ? (a) : (b))
#define MIN(a, b)		((a) < (b) ? (a) : (b))
#define MAX3(a, b, c)	MAX(a, MAX(b, c))
#define MIN3(a, b, c)	MIN(a, MIN(b, c))

// Error screen.
void panic(char *msg);

// Safe malloc/calloc/realloc and printf functions which 
// jump to debugging error screens if a problem occurs.
void *safe_malloc(size_t size);
void *safe_calloc(size_t num, size_t elsize);
void *safe_realloc(void *ptr, size_t size);
// Implementations of itoa and reverse.
int my_itoa(long int n, char s[]);
void reverse(char s[]);
// Integer power function. (Faster than floating point pow.)
long int intpow(int x, int y);
// Lat/Long to string.
void fpllstring(float ll, int digits, char *s);

#endif
