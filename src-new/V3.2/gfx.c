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

// used by some debug code
long int delaytmp;

#include "gfx.h"
#include "useful.h"
#include "fonts.h"
#include <stdlib.h>

/**
 * The GFX files handle the management of the display surfaces. 
 * They implement the basic drawing functions and the display
 * buffers. But, they do not handle the actual OSD output or 
 * timing; that is managed by the OSD files.
 */

// We define four buffers: two level buffers and two mask buffers.
// All buffers are identical in size and type.
uint16_t buffer0_level[BUFF_WORDS] FAR;
uint16_t buffer0_mask[BUFF_WORDS] FAR;
uint16_t buffer1_level[BUFF_WORDS] FAR;
uint16_t buffer1_mask[BUFF_WORDS] FAR;

// We define pointers to each of these buffers.
uint16_t *draw_buffer_level;
uint16_t *draw_buffer_mask;
uint16_t *disp_buffer_level;
uint16_t *disp_buffer_mask;

/**
 * init_osd: Initialize the OSD buffers and internal 
 * state variables.
 */
void init_gfx()
{
	draw_buffer_level = buffer0_level;
	draw_buffer_mask = buffer0_mask;
	disp_buffer_level = buffer1_level;
	disp_buffer_mask = buffer1_mask;
	// Fill the buffers.
	fill_buffer(draw_buffer_level, 0x0000);
	fill_buffer(draw_buffer_mask, 0x0000);
	fill_buffer(disp_buffer_level, 0x0000);
	fill_buffer(disp_buffer_mask, 0x0000);
}

/**
 * fill_buffer: Fill a buffer (given by a pointer)
 * with one word of data.
 */
void fill_buffer(uint16_t *buff, uint16_t word)
{
	int i = BUFF_WORDS, j;
	while(i--)
	{
		*buff++ = word;
	}
}

/**
 * fill_buffer_rand: Fill a buffer (given by a pointer)
 * with random data.
 */
void fill_buffer_rand(uint16_t *buff)
{
	int i = BUFF_WORDS, j;
	while(i--)
	{
		*buff++ = rand() + rand();
	}
}

/**
 * write_pixel: Write a pixel at an x,y position to a given surface.
 *
 * @param	buff	pointer to buffer to write in
 * @param	x		x coordinate
 * @param	y		y coordinate
 * @param	mode	0 = clear bit, 1 = set bit, 2 = toggle bit
 */
void write_pixel(uint16_t *buff, unsigned int x, unsigned int y, int mode)
{
	CHECK_COORDS(x, y);
	// Determine the bit in the word to be set and the word
	// index to set it in.
	int bitnum = CALC_BIT_IN_WORD(x);
	int wordnum = CALC_BUFF_ADDR(x, y);
	// Apply a mask.
	uint16_t mask = 1 << (15 - bitnum);
	WRITE_WORD_MODE(buff, wordnum, mask, mode);
}

/**
 * write_pixel_lm: write the pixel on both surfaces (level and mask.)
 * Uses current draw buffer.
 *
 * @param	x		x coordinate
 * @param	y		y coordinate
 * @param	mmode	0 = clear, 1 = set, 2 = toggle
 * @param	lmode	0 = black, 1 = white, 2 = toggle
 */
void write_pixel_lm(unsigned int x, unsigned int y, int mmode, int lmode)
{
	CHECK_COORDS(x, y);
	// Determine the bit in the word to be set and the word
	// index to set it in.
	int bitnum = CALC_BIT_IN_WORD(x);
	int wordnum = CALC_BUFF_ADDR(x, y);
	// Apply the masks.
	uint16_t mask = 1 << (15 - bitnum);
	WRITE_WORD_MODE(draw_buffer_mask, wordnum, mask, mmode);
	WRITE_WORD_MODE(draw_buffer_level, wordnum, mask, lmode);
}

/**
 * write_hline: optimised horizontal line writing algorithm
 *
 * @param	buff	pointer to buffer to write in
 * @param	x0		x0 coordinate
 * @param	x1		x1 coordinate
 * @param	y		y coordinate
 * @param	mode	0 = clear, 1 = set, 2 = toggle
 */
void write_hline(uint16_t *buff, unsigned int x0, unsigned int x1, unsigned int y, int mode)
{
	CLIP_COORDS(x0, y);
	CLIP_COORDS(x1, y);
	if(x0 > x1)
	{
		SWAP(x0, x1);
	}
	if(x0 == x1) return;
	/* This is an optimised algorithm for writing horizontal lines. 
	 * We begin by finding the addresses of the x0 and x1 points. */
	int addr0 = CALC_BUFF_ADDR(x0, y);
	int addr1 = CALC_BUFF_ADDR(x1, y);
	int addr0_bit = CALC_BIT_IN_WORD(x0);
	int addr1_bit = CALC_BIT_IN_WORD(x1);
	int mask, mask_l, mask_r, i;
	/* If the addresses are equal, we only need to write one word
	 * which is an island. */
	if(addr0 == addr1)
	{
		mask = COMPUTE_HLINE_ISLAND_MASK(addr0_bit, addr1_bit);
		WRITE_WORD_MODE(buff, addr0, mask, mode);
	}
	/* Otherwise we need to write the edges and then the middle. */
	else
	{
		mask_l = COMPUTE_HLINE_EDGE_L_MASK(addr0_bit);
		mask_r = COMPUTE_HLINE_EDGE_R_MASK(addr1_bit);
		WRITE_WORD_MODE(buff, addr0, mask_l, mode);
		WRITE_WORD_MODE(buff, addr1, mask_r, mode);
		// Now write 0xffff words from start+1 to end-1.
		for(i = addr0 + 1; i <= addr1 - 1; i++)
		{
			WRITE_WORD_MODE(buff, i, 0xffff, mode);
		}
	}
}

/**
 * write_hline_lm: write both level and mask buffers.
 *
 * @param	x0		x0 coordinate
 * @param	x1		x1 coordinate
 * @param	y		y coordinate
 * @param	lmode	0 = clear, 1 = set, 2 = toggle
 * @param	mmode	0 = clear, 1 = set, 2 = toggle
 */
void write_hline_lm(unsigned int x0, unsigned int x1, unsigned int y, int lmode, int mmode)
{
	// TODO: an optimisation would compute the masks and apply to
	// both buffers simultaneously.
	write_hline(draw_buffer_level, x0, x1, y, lmode);
	write_hline(draw_buffer_mask, x0, x1, y, mmode);
}

/**
 * write_hline_outlined: outlined horizontal line with varying endcaps
 * Always uses draw buffer.
 *
 * @param	x0			x0 coordinate
 * @param	x1			x1 coordinate
 * @param	y			y coordinate
 * @param	endcap0		0 = none, 1 = single pixel, 2 = full cap
 * @param	endcap1		0 = none, 1 = single pixel, 2 = full cap
 * @param	mode		0 = black outline, white body, 1 = white outline, black body
 * @param	mmode		0 = clear, 1 = set, 2 = toggle
 */
void write_hline_outlined(unsigned int x0, unsigned int x1, unsigned int y, int endcap0, int endcap1, int mode, int mmode)
{
	int stroke, fill;
	SETUP_STROKE_FILL(stroke, fill, mode)
	// Draw the main body of the line.
	write_hline_lm(x0 + 1, x1 - 1, y - 1, stroke, mmode); 
	write_hline_lm(x0 + 1, x1 - 1, y + 1, stroke, mmode);
	write_hline_lm(x0 + 1, x1 - 1, y, fill, mmode);
	// Draw the endcaps, if any.
	DRAW_ENDCAP_HLINE(endcap0, x0, y, stroke, fill, mmode);
	DRAW_ENDCAP_HLINE(endcap1, x1, y, stroke, fill, mmode);
}

/**
 * swap_buffers: Swaps the two buffers. Contents in the display
 * buffer is seen on the output and the display buffer becomes
 * the new draw buffer.
 */
void swap_buffers()
{
	// While we could use XOR swap this is more reliable and
	// dependable and it's only called a few times per second.
	// Many compliers should optimise these to EXCH instructions.
	uint16_t *tmp;
	SWAP_BUFFS(tmp, disp_buffer_mask, draw_buffer_mask);
	SWAP_BUFFS(tmp, disp_buffer_level, draw_buffer_level);
}

/**
 * write_vline: optimised vertical line writing algorithm
 *
 * @param	buff	pointer to buffer to write in
 * @param	x		x coordinate
 * @param	y0		y0 coordinate
 * @param	y1		y1 coordinate
 * @param	mode	0 = clear, 1 = set, 2 = toggle
 */
void write_vline(uint16_t *buff, unsigned int x, unsigned int y0, unsigned int y1, int mode)
{
	unsigned int a;
	CLIP_COORDS(x, y0);
	CLIP_COORDS(x, y1);
	if(y0 > y1)
	{
		SWAP(y0, y1);
	}
	if(y0 == y1) return;
	/* This is an optimised algorithm for writing vertical lines. 
	 * We begin by finding the addresses of the x,y0 and x,y1 points. */
	int addr0 = CALC_BUFF_ADDR(x, y0);
	int addr1 = CALC_BUFF_ADDR(x, y1);
	/* Then we calculate the pixel data to be written. */
	int bitnum = CALC_BIT_IN_WORD(x);
	uint16_t mask = 1 << (15 - bitnum);
	/* Run from addr0 to addr1 placing pixels. Increment by the number
	 * of words n each graphics line. */
	for(a = addr0; a <= addr1; a += DISP_WIDTH / 16)
	{
		WRITE_WORD_MODE(buff, a, mask, mode);
	}
}

/**
 * write_vline_lm: write both level and mask buffers.
 *
 * @param	x		x coordinate
 * @param	y0		y0 coordinate
 * @param	y1		y1 coordinate
 * @param	lmode	0 = clear, 1 = set, 2 = toggle
 * @param	mmode	0 = clear, 1 = set, 2 = toggle
 */
void write_vline_lm(unsigned int x, unsigned int y0, unsigned int y1, int lmode, int mmode)
{
	// TODO: an optimisation would compute the masks and apply to
	// both buffers simultaneously.
	write_vline(draw_buffer_level, x, y0, y1, lmode);
	write_vline(draw_buffer_mask, x, y0, y1, mmode);
}

/**
 * write_hline_outlined: outlined horizontal line with varying endcaps
 * Always uses draw buffer.
 *
 * @param	x			x coordinate
 * @param	y0			y0 coordinate
 * @param	y1			y1 coordinate
 * @param	endcap0		0 = none, 1 = single pixel, 2 = full cap
 * @param	endcap1		0 = none, 1 = single pixel, 2 = full cap
 * @param	mode		0 = black outline, white body, 1 = white outline, black body
 * @param	mmode		0 = clear, 1 = set, 2 = toggle
 */
void write_vline_outlined(unsigned int x, unsigned int y0, unsigned int y1, int endcap0, int endcap1, int mode, int mmode)
{
	int stroke, fill;
	SETUP_STROKE_FILL(stroke, fill, mode);
	// Draw the main body of the line.
	write_vline_lm(x - 1, y0 + 1, y1 - 1, stroke, mmode); 
	write_vline_lm(x + 1, y0 + 1, y1 - 1, stroke, mmode);
	write_vline_lm(x, y0 + 1, y1 - 1, fill, mmode);
	// Draw the endcaps, if any.
	DRAW_ENDCAP_VLINE(endcap0, x, y0, stroke, fill, mmode);
	DRAW_ENDCAP_VLINE(endcap1, x, y1, stroke, fill, mmode);
}

/**
 * write_filled_rectangle: draw a filled rectangle.
 *
 * Uses an optimised algorithm which is similar to the horizontal 
 * line writing algorithm, but optimised for writing the lines 
 * multiple times without recalculating lots of stuff.
 *
 * @param	buff	pointer to buffer to write in
 * @param	x		x coordinate (left)
 * @param	y		y coordinate (top)
 * @param	width	rectangle width
 * @param	height	rectangle height
 * @param	mode	0 = clear, 1 = set, 2 = toggle
 */
void write_filled_rectangle(uint16_t *buff, unsigned int x, unsigned int y, unsigned int width, unsigned int height, int mode)
{
	int yy, addr0_old, addr1_old;
	CHECK_COORDS(x, y);
	CHECK_COORD_X(x + width);
	CHECK_COORD_Y(y + height);
	if(width <= 0 || height <= 0) return;
	// Calculate as if the rectangle was only a horizontal line. We then
	// step these addresses through each row until we iterate `height` times. 
	int addr0 = CALC_BUFF_ADDR(x, y);
	int addr1 = CALC_BUFF_ADDR(x + width, y);
	int addr0_bit = CALC_BIT_IN_WORD(x);
	int addr1_bit = CALC_BIT_IN_WORD(x + width);
	int mask, mask_l, mask_r, i;
	// If the addresses are equal, we need to write one word vertically.
	if(addr0 == addr1)
	{
		mask = COMPUTE_HLINE_ISLAND_MASK(addr0_bit, addr1_bit);
		while(height--)
		{
			WRITE_WORD_MODE(buff, addr0, mask, mode);
			addr0 += DISP_WIDTH / 16;
		}
	}
	// Otherwise we need to write the edges and then the middle repeatedly. 
	else
	{
		mask_l = COMPUTE_HLINE_EDGE_L_MASK(addr0_bit);
		mask_r = COMPUTE_HLINE_EDGE_R_MASK(addr1_bit);
		// Write edges first.
		yy = 0;
		addr0_old = addr0;
		addr1_old = addr1;
		while(yy < height)
		{
			WRITE_WORD_MODE(buff, addr0, mask_l, mode);
			WRITE_WORD_MODE(buff, addr1, mask_r, mode);
			addr0 += DISP_WIDTH / 16;
			addr1 += DISP_WIDTH / 16;
			yy++;
		}
		// Now write 0xffff words from start+1 to end-1 for each row.
		yy = 0;
		addr0 = addr0_old;
		addr1 = addr1_old;
		while(yy < height)
		{
			for(i = addr0 + 1; i <= addr1 - 1; i++)
			{
				WRITE_WORD_MODE(buff, i, 0xffff, mode);
			}
			addr0 += DISP_WIDTH / 16;
			addr1 += DISP_WIDTH / 16;
			yy++;
		}
	}
}

/**
 * write_filled_rectangle_lm: draw a filled rectangle on both draw buffers.
 *
 * @param	x		x coordinate (left)
 * @param	y		y coordinate (top)
 * @param	width	rectangle width
 * @param	height	rectangle height
 * @param	lmode	0 = clear, 1 = set, 2 = toggle
 * @param	mmode	0 = clear, 1 = set, 2 = toggle
 */
void write_filled_rectangle_lm(unsigned int x, unsigned int y, unsigned int width, unsigned int height, int lmode, int mmode)
{
	write_filled_rectangle(draw_buffer_mask, x, y, width, height, mmode);
	write_filled_rectangle(draw_buffer_level, x, y, width, height, lmode);
}

/**
 * write_rectangle_outlined: draw an outline of a rectangle. Essentially
 * a convenience wrapper for draw_hline_outlined and draw_vline_outlined.
 *
 * @param	x		x coordinate (left)
 * @param	y		y coordinate (top)
 * @param	width	rectangle width
 * @param	height	rectangle height
 * @param	mode	0 = black outline, white body, 1 = white outline, black body
 * @param	mmode	0 = clear, 1 = set, 2 = toggle
 */
void write_rectangle_outlined(unsigned int x, unsigned int y, int width, int height, int mode, int mmode)
{
	//CHECK_COORDS(x, y);
	//CHECK_COORDS(x + width, y + height);
	//if((x + width) > DISP_WIDTH) width = DISP_WIDTH - x;
	//if((y + height) > DISP_HEIGHT) height = DISP_HEIGHT - y;
	write_hline_outlined(x, x + width, y, ENDCAP_ROUND, ENDCAP_ROUND, mode, mmode);
	write_hline_outlined(x, x + width, y + height, ENDCAP_ROUND, ENDCAP_ROUND, mode, mmode);
	write_vline_outlined(x, y, y + height, ENDCAP_ROUND, ENDCAP_ROUND, mode, mmode);
	write_vline_outlined(x + width, y, y + height, ENDCAP_ROUND, ENDCAP_ROUND, mode, mmode);
}

/**
 * write_circle: draw the outline of a circle on a given buffer,
 * with an optional dash pattern for the line instead of a normal line.
 *
 * @param	buff	pointer to buffer to write in
 * @param	cx		origin x coordinate
 * @param	cy		origin y coordinate
 * @param	r		radius
 * @param	dashp	dash period (pixels) - zero for no dash
 * @param	mode	0 = clear, 1 = set, 2 = toggle
 */
void write_circle(uint16_t *buff, unsigned int cx, unsigned int cy, unsigned int r, unsigned int dashp, int mode)
{
	CHECK_COORDS(cx, cy);
	int error = -r, x = r, y = 0;
	while(x >= y)
	{
		if(dashp == 0 || (y % dashp) < (dashp / 2))
		{
			CIRCLE_PLOT_8(buff, cx, cy, x, y, mode);
		}
		error += (y * 2) + 1;
		y++;
		if(error >= 0)
		{
			--x;
			error -= x * 2;
		}
	}
}

/**
 * write_circle_outlined: draw an outlined circle on the draw buffer.
 *
 * @param	cx		origin x coordinate
 * @param	cy		origin y coordinate
 * @param	r		radius
 * @param	dashp	dash period (pixels) - zero for no dash
 * @param	bmode	0 = 4-neighbour border, 1 = 8-neighbour border
 * @param	mode	0 = black outline, white body, 1 = white outline, black body
 * @param	mmode	0 = clear, 1 = set, 2 = toggle
 */
void write_circle_outlined(unsigned int cx, unsigned int cy, unsigned int r, unsigned int dashp, int bmode, int mode, int mmode)
{
	int stroke, fill;
	CHECK_COORDS(cx, cy);
	SETUP_STROKE_FILL(stroke, fill, mode);
	// This is a two step procedure. First, we draw the outline of the 
	// circle, then we draw the inner part.
	int error = -r, x = r, y = 0;
	while(x >= y)
	{
		if(dashp == 0 || (y % dashp) < (dashp / 2))
		{
			CIRCLE_PLOT_8(draw_buffer_mask, cx, cy, x + 1, y, mmode);
			CIRCLE_PLOT_8(draw_buffer_level, cx, cy, x + 1, y, stroke);
			CIRCLE_PLOT_8(draw_buffer_mask, cx, cy, x, y + 1, mmode);
			CIRCLE_PLOT_8(draw_buffer_level, cx, cy, x, y + 1, stroke);
			CIRCLE_PLOT_8(draw_buffer_mask, cx, cy, x - 1, y, mmode);
			CIRCLE_PLOT_8(draw_buffer_level, cx, cy, x - 1, y, stroke);
			CIRCLE_PLOT_8(draw_buffer_mask, cx, cy, x, y - 1, mmode);
			CIRCLE_PLOT_8(draw_buffer_level, cx, cy, x, y - 1, stroke);
			if(bmode == 1)
			{
				CIRCLE_PLOT_8(draw_buffer_mask, cx, cy, x + 1, y + 1, mmode);
				CIRCLE_PLOT_8(draw_buffer_level, cx, cy, x + 1, y + 1, stroke);
				CIRCLE_PLOT_8(draw_buffer_mask, cx, cy, x - 1, y - 1, mmode);
				CIRCLE_PLOT_8(draw_buffer_level, cx, cy, x - 1, y - 1, stroke);
			}
		}
		error += (y * 2) + 1;
		y++;
		if(error >= 0)
		{
			--x;
			error -= x * 2;
		}
	}
	error = -r;
	x = r;
	y = 0;
	while(x >= y)
	{
		if(dashp == 0 || (y % dashp) < (dashp / 2))
		{
			CIRCLE_PLOT_8(draw_buffer_mask, cx, cy, x, y, mmode);
			CIRCLE_PLOT_8(draw_buffer_level, cx, cy, x, y, fill);
		}
		error += (y * 2) + 1;
		y++;
		if(error >= 0)
		{
			--x;
			error -= x * 2;
		}
	}
}

/**
 * write_circle_filled: fill a circle on a given buffer.
 *
 * @param	buff	pointer to buffer to write in
 * @param	cx		origin x coordinate
 * @param	cy		origin y coordinate
 * @param	r		radius
 * @param	mode	0 = clear, 1 = set, 2 = toggle
 */
void write_circle_filled(uint16_t *buff, unsigned int cx, unsigned int cy, unsigned int r, int mode)
{
	CHECK_COORDS(cx, cy);
	int error = -r, x = r, y = 0, xch = 0;
	// It turns out that filled circles can take advantage of the midpoint
	// circle algorithm. We simply draw very fast horizontal lines across each
	// pair of X,Y coordinates. In some cases, this can even be faster than 
	// drawing an outlined circle!
	//
	// Due to multiple writes to each set of pixels, we have a special exception
	// for when using the toggling draw mode.
	while(x >= y)
	{
		if(y != 0)
		{
			write_hline(buff, cx - x, cx + x, cy + y, mode);
			write_hline(buff, cx - x, cx + x, cy - y, mode);
			if(mode != 2 || (mode == 2 && xch && (cx - x) != (cx - y)))
			{
				write_hline(buff, cx - y, cx + y, cy + x, mode);
				write_hline(buff, cx - y, cx + y, cy - x, mode);
				xch = 0;
			}
		}
		error += (y * 2) + 1;
		y++;
		if(error >= 0)
		{
			--x;
			xch = 1;
			error -= x * 2;
		}
	}
	// Handle toggle mode.
	if(mode == 2)
	{
		write_hline(buff, cx - r, cx + r, cy, mode);
	}
}

/**
 * write_line: Draw a line of arbitrary angle.
 *
 * @param	buff	pointer to buffer to write in
 * @param	x0		first x coordinate
 * @param	y0		first y coordinate
 * @param	x1		second x coordinate
 * @param	y1		second y coordinate
 * @param	mode	0 = clear, 1 = set, 2 = toggle
 */
void write_line(uint16_t *buff, unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, int mode)
{
	// Based on http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
	int steep = abs(y1 - y0) > abs(x1 - x0);
	if(steep)
	{
		SWAP(x0, y0);
		SWAP(x1, y1);
	}
	if(x0 > x1)
	{
		SWAP(x0, x1);
		SWAP(y0, y1);
	}
	int deltax = x1 - x0;
	int deltay = abs(y1 - y0);
	int error = deltax / 2;
	int ystep;
	int y = y0;
	int x;
	if(y0 < y1)
		ystep = 1;
	else
		ystep = -1;
	for(x = x0; x < x1; x++)
	{
		if(steep)
			write_pixel(buff, y, x, mode);
		else
			write_pixel(buff, x, y, mode);
		error -= deltay;
		if(error < 0)
		{
			y += ystep;
			error += deltax;
		}
	}
}

/**
 * write_line_outlined: Draw a line of arbitrary angle, with an outline.
 *
 * @param	buff	pointer to buffer to write in
 * @param	x0		first x coordinate
 * @param	y0		first y coordinate
 * @param	x1		second x coordinate
 * @param	y1		second y coordinate
 * @param	mode	0 = clear, 1 = set, 2 = toggle
 */
void write_line_outlined(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, int mmode, int mode)
{
	int stroke, fill;
	SETUP_STROKE_FILL(stroke, fill, mode);
	// To draw an outlined line, we first process the outside of the line, then
	// draw the inside part, similar to circles. 
	unsigned int steep = abs(y1 - y0) > abs(x1 - x0);
	if(steep)
	{
		SWAP(x0, y0);
		SWAP(x1, y1);
	}
	if(x0 > x1)
	{
		SWAP(x0, x1);
		SWAP(y0, y1);
	}
	unsigned int deltax = x1 - x0;
	unsigned int deltay = abs(y1 - y0);
	unsigned int error = deltax / 2;
	unsigned int ystep, y = y0, x;
	if(y0 < y1)
		ystep = 1;
	else
		ystep = -1;
	// TODO
}

/**
 * write_word_misaligned: Write a misaligned word across two addresses
 * with an x offset.
 *
 * This allows for many pixels to be set in one write.
 *
 * @param	buff	buffer to write in
 * @param	word	word to write (16 bits)
 * @param	addr	address of first word
 * @param	xoff	x offset (0-15)
 * @param	mode	0 = clear, 1 = set, 2 = toggle
 */
void write_word_misaligned(uint16_t *buff, uint16_t word, unsigned int addr, unsigned int xoff, int mode)
{
	uint16_t firstmask = word >> xoff;
	uint16_t lastmask = word << (16 - xoff);
	WRITE_WORD_MODE(buff, addr, firstmask, mode);
	if(xoff > 0)
	{
		WRITE_WORD_MODE(buff, addr + 1, lastmask, mode);
	}
}

/**
 * write_word_misaligned_lm: Write a misaligned word across two 
 * words, in both level and mask buffers. This is core to the text
 * writing routines.
 *
 * @param	buff	buffer to write in
 * @param	word	word to write (16 bits)
 * @param	addr	address of first word
 * @param	xoff	x offset (0-15)
 * @param	lmode	0 = clear, 1 = set, 2 = toggle
 * @param	mmode	0 = clear, 1 = set, 2 = toggle
 */
void write_word_misaligned_lm(uint16_t wordl, uint16_t wordm, unsigned int addr, unsigned int xoff, int lmode, int mmode)
{
	write_word_misaligned(draw_buffer_level, wordl, addr, xoff, lmode);
	write_word_misaligned(draw_buffer_mask, wordm, addr, xoff, mmode);
}

/**
 * fetch_font_info: Fetch font info structs.
 *
 * @param	ch		character
 * @param	font	font id
 */
int fetch_font_info(char ch, int font, struct FontEntry *font_info, char *lookup)
{
	// First locate the font struct.
	if(font > SIZEOF_ARRAY(fonts))
		return 0; // font does not exist, exit.
	// Load the font info; IDs are always sequential.
	*font_info = fonts[font];
	// Locate character in font lookup table. (If required.)
	if(lookup != NULL)
	{
		*lookup = font_info->lookup[ch];
		if(*lookup == 0xff)
			return 0; // character doesn't exist, don't bother writing it.
	}
	return 1;
}

/**
 * write_char: Draw a character on the current draw buffer.
 * Currently supports outlined characters and characters with 
 * a width of up to 8 pixels.
 *
 * @param	ch		character to write
 * @param	x		x coordinate (left)
 * @param	y		y coordinate (top)
 * @param	flags	flags to write with (see gfx.h)
 * @param	font	font to use
 */
void write_char(char ch, unsigned int x, unsigned int y, int flags, int font)
{
	int i, yy, addr_temp, row, row_temp, xshift;
	uint16_t and_mask, or_mask, level_bits;
	struct FontEntry font_info;
	char lookup;
	fetch_font_info(ch, font, &font_info, &lookup);
	// Compute starting address (for x,y) of character.
	int addr = CALC_BUFF_ADDR(x, y);
	int wbit = CALC_BIT_IN_WORD(x);
	// If font only supports lowercase or uppercase, make the letter 
	// lowercase or uppercase.
	if(font_info.flags & FONT_LOWERCASE_ONLY)
		ch = tolower(ch);
	if(font_info.flags & FONT_UPPERCASE_ONLY)
		ch = toupper(ch);
	fetch_font_info(ch, font, &font_info, &lookup);
	// How big is the character? We handle characters up to 8 pixels
	// wide for now. Support for large characters may be added in future.
	if(font_info.width <= 8)
	{
		// Ensure we don't overflow.
		if(x + wbit > DISP_WIDTH) 
			return;
		// Load data pointer.
		row = lookup * font_info.height * 2;
		row_temp = row;
		addr_temp = addr;
		xshift = 16 - font_info.width;
		// We can write mask words easily.
		for(yy = y; yy < y + font_info.height; yy++)
		{
			write_word_misaligned(draw_buffer_mask, font_info.data[row] << xshift, addr, wbit, 1);
			addr += DISP_WIDTH / 16;
			row++;
		}
		// Level bits are more complicated. We need to set or clear
		// level bits, but only where the mask bit is set; otherwise,
		// we need to leave them alone. To do this, for each word, we
		// construct an AND mask and an OR mask, and apply each individually.
		row = row_temp;
		addr = addr_temp;
		for(yy = y; yy < y + font_info.height; yy++)
		{
			level_bits = font_info.data[row + font_info.height];
			if(!(flags & FONT_INVERT)) // data is normally inverted
				level_bits = ~level_bits;
			or_mask = font_info.data[row] << xshift;
			and_mask = (font_info.data[row] & level_bits) << xshift;
			write_word_misaligned(draw_buffer_level, or_mask, addr, wbit, 1);
			// If we're not bold write the AND mask.
			if(!(flags & FONT_BOLD))
				write_word_misaligned(draw_buffer_level, and_mask, addr, wbit, 0);
			addr += DISP_WIDTH / 16;
			row++;
		}
	}
}

/**
 * calc_text_dimensions: Calculate the dimensions of a 
 * string in a given font. Supports new lines and
 * carriage returns in text.
 *
 * @param	str			string to calculate dimensions of
 * @param	font_info	font info structure
 * @param	xs			horizontal spacing
 * @param	ys			vertical spacing
 * @param	dim			return result: struct FontDimensions
 */
void calc_text_dimensions(char *str, struct FontEntry font, int xs, int ys, struct FontDimensions *dim)
{
	int max_length = 0, line_length = 0, lines = 1;
	while(*str != 0)
	{
		line_length++;
		if(*str == '\n' || *str == '\r')
		{
			if(line_length > max_length)
				max_length = line_length;
			line_length = 0;
			lines++;
		}
		str++;
	}
	if(line_length > max_length)
		max_length = line_length;
	dim->width = max_length * (font.width + xs);
	dim->height = lines * (font.height + ys);
}

/**
 * write_string: Draw a string on the screen with certain
 * alignment parameters.
 *
 * @param	str		string to write
 * @param	x		x coordinate
 * @param	y		y coordinate
 * @param	xs		horizontal spacing
 * @param	ys		horizontal spacing
 * @param	va 		vertical align
 * @param	ha		horizontal align
 * @param	flags	flags (passed to write_char)
 * @param	font	font
 */
void write_string(char *str, unsigned int x, unsigned int y, unsigned int xs, unsigned int ys, int va, int ha, int flags, int font)
{
	int xx, yy, xx_original;
	struct FontEntry font_info;
	struct FontDimensions dim;
	char lookup;
	// Determine font info and dimensions/position of the string.
	fetch_font_info(0, font, &font_info, NULL);
	calc_text_dimensions(str, font_info, xs, ys, &dim);
	switch(va)
	{
		case TEXT_VA_TOP: 		yy = y; break;
		case TEXT_VA_MIDDLE:	yy = y - (dim.height / 2); break;
		case TEXT_VA_BOTTOM: 	yy = y - dim.height; break;
	}
	switch(ha)
	{
		case TEXT_HA_LEFT:		xx = x; break;
		case TEXT_HA_CENTER:	xx = x - (dim.width / 2); break;
		case TEXT_HA_RIGHT:		xx = x - dim.width; break;
	}
	// Then write each character.
	xx_original = xx;
	while(*str != 0)
	{
		if(*str == '\n' || *str == '\r')
		{
			yy += ys + font_info.height;
			xx = xx_original;
		}
		else
		{
			if(xx >= 0 && xx < DISP_WIDTH)
				write_char(*str, xx, yy, flags, font);
			xx += font_info.width + xs;
		}
		str++;
	}
}