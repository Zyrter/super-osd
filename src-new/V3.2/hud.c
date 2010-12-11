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
#include "hud.h"
#include "gfx.h"

/*
 * Head-up display routines.
 */
 
/**
 * hud_draw_vertical_scale: Draw a vertical scale.
 * 
 * @param	v				value to display as an integer
 * @param	range			range about value to display (+/- range/2 each direction)
 * @param	halign			horizontal alignment: -1 = left, +1 = right.
 * @param	height			height of scale
 * @param	x				x displacement (typ. 0)
 * @param	y				y displacement (typ. half display height)
 * @param	majtick_len		major tick length
 * @param	mintick_len		minor tick length
 * @param	flags			special flags (see hud.h.)
 */
void hud_draw_vertical_scale(int v, int range, int halign, int x, int y, int height, int majtick_len, int mintick_len, int flags)
{
	// Halign should be in a small span. Future versions may use floating point
	// maths to allow the scale to have varying degrees of halign, but floating
	// point slows down things.
	MY_ASSERT(halign >= -1 && halign <= 1);
	// Compute position of all sub-elements.
	int majtick_start = x + (halign * (DISP_WIDTH / 2));
	int majtick_end = x + (halign * (DISP_WIDTH / 2)) + (halign * majtick_len);
	int mintick_start = x + (halign * (DISP_WIDTH / 2));
	int mintick_end = x + (halign * (DISP_WIDTH / 2)) + (halign * mintick_len);
}