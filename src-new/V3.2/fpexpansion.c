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
 * Adds functions to the Microchip Q16 library.
 */

/**
 * multiply_sign: Correct the sign of a signed multiply
 * using an unsigned multiply routine.
 *
 * @param	x	multiply result
 * @param	a	input a
 * @param	b	input b
 *
 * @return	fixed result
 */
_Q16 multiply_sign(_Q16 x, _Q16 a, _Q16 b)
{
	if(a < 0 && b < 0) // negative * negative: positive
		return x;
	else if(a >= 0 && b < 0) // positive * negative: negative
		return _Q16neg(x);
	else if(a < 0 && b >= 0) // negative * positive: negative
		return _Q16neg(x);
	else if(a >= 0 && b >= 0) // positive * positive: positive
		return x;
}
 
/**
 * multiplyQ16xQ16: Multiply two Q16 numbers together.
 *
 * @param	a	first input
 * @param	b	second input
 *
 * @return	result of multiplication
 */
_Q16 multiplyQ16xQ16(_Q16 a, _Q16 b)
{
	// are signs correct?
	return multiply_sign(_Q16mac(a, b, 0), a, b);
}

/**
 * multiplyQ16xQ15: Multiply a Q16 number with a Q15 number.
 *
 * @param	a	first input
 * @param	b	second input
 *
 * @return	result of multiplication
 */
_Q16 multiplyQ16xQ15(_Q16 a, _Q15 b)
{
	// are signs correct?
	_Q16 bb = b;
	return multiply_sign(_Q16mac(a, bb, 0), a, bb);
}

// other permutation
#define multiplyQ15xQ16(a, b)	multiplyQ16xQ15(b, a)

/**
 * multiplyQ15xQ15: Multiply a Q15 number with another Q15 number.
 *
 * @param	a	first input
 * @param	b	second input
 *
 * @return	result of multiplication
 */
_Q16 multiplyQ15xQ15(_Q15 a, _Q15 b)
{
	// are signs correct?
	_Q16 aa = a;
	_Q16 bb = b;
	return multiply_sign(_Q16mac(aa, bb, 0), aa, bb);
}

/**
 * squareQ16: Square a Q16 number.
 *
 * @param	x		input
 *
 * @return	x * x
 */
_Q16 squareQ16(_Q16 x)
{
	return multiplyQ16xQ16(x, x);
}

/**
 * squareQ15: Square a Q15 number.
 *
 * @param	x		input
 *
 * @return	x * x
 */
_Q16 squareQ15(_Q15 x)
{
	return multiplyQ15xQ15(x, x);
}

/**
 * divideQ16byQ16: Computes a / b. For b = 0 (division by zero)
 * it returns 0.
 *
 * @param	a	numerator
 * @param	b	denominator
 *
 * @return	result of division
 */
_Q16 divideQ16byQ16(_Q16 a, _Q16 b)
{
	if(b == 0)
		return 0;
	return multiplyQ16xQ16(a, _Q16reciprocalQ16(b));
}
