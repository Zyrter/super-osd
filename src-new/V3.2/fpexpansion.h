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

#include <libq.h>

/**
 * Adds functions to the Microchip fixed point library.
 */

_Q16 multiplyQ16xQ16(_Q16 a, _Q16 b);
_Q16 multiplyQ16xQ15(_Q16 a, _Q15 b);
#define multiplyQ15xQ16(a, b)	multiplyQ16xQ15(b, a) // other permutation
_Q16 multiplyQ15xQ15(_Q15 a, _Q15 b);
_Q16 squareQ16(_Q16 x);
_Q16 squareQ15(_Q15 x);
_Q16 divideQ16byQ16(_Q16 a, _Q16 bs);
