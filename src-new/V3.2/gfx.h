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

#ifndef	GFX_H
#define	GFX_H

#include "fonts.h"

typedef	unsigned short uint16_t;

#define FAR	__attribute__((far))

// We have a 192x128 pixel display.
#define	DISP_WIDTH	192
#define	DISP_HEIGHT	128

// We define four buffers: two level buffers and two mask buffers.
// All buffers are identical in size and type.
#define	BUFF_SIZE	((192 / 8) * 128)
#define BUFF_WORDS	(BUFF_SIZE / 2)

// Macros for computing addresses and bit positions.
// NOTE: /16 in y is because we are addressing by word not byte.
#define	CALC_BUFF_ADDR(x, y)	(((x) / 16) + ((y) * (DISP_WIDTH / 16)))
#define	CALC_BIT_IN_WORD(x)		((x) & 15)

// Macro for initializing stroke/fill modes. Add new modes here
// if necessary.
#define SETUP_STROKE_FILL(stroke, fill, mode) \
	stroke = 0; fill = 0; \
	if(mode == 0) { stroke = 0; fill = 1; } \
	if(mode == 1) { stroke = 1; fill = 0; } \

// Debugging macro. If enabled delays writes so they are more visible.
extern long int delaytmp;
#define ENABLE_DELAY_WRITES 0

#if ENABLE_DELAY_WRITES == 1
#define DEBUG_DELAY { delaytmp = 10000; while(delaytmp--); }
#else
#define DEBUG_DELAY
#endif

// Macro for writing a word with a mode (NAND = clear, OR = set, XOR = toggle)
// at a given position
#define WRITE_WORD_MODE(buff, addr, mask, mode) \
	switch(mode) { \
		case 0: buff[addr] = buff[addr] & ~mask; break; \
		case 1:	buff[addr] |= mask; break; \
		case 2: buff[addr] ^= mask; break; } \
	DEBUG_DELAY;

// Horizontal line calculations. 
// This computes an island mask.
#define	COMPUTE_HLINE_ISLAND_MASK(b0, b1) (((1 << (b0)) - 1) ^ ((1 << ((b1) + 1)) - 1));
// Edge cases are simpler.
#define	COMPUTE_HLINE_EDGE_L_MASK(b) ((1 << (16 - (b))) - 1)
#define	COMPUTE_HLINE_EDGE_R_MASK(b) (~((1 << (15 - (b))) - 1))

// Line endcaps (for horizontal and vertical lines.)
#define ENDCAP_NONE		0
#define ENDCAP_ROUND	1
#define ENDCAP_FLAT 	2

#define	DRAW_ENDCAP_HLINE(e, x, y, s, f, l) \
	if((e) == ENDCAP_ROUND) /* single pixel endcap */ \
	{ write_pixel_lm(x, y, f, l); } \
	else if((e) == ENDCAP_FLAT) /* flat endcap: FIXME, quicker to draw a vertical line(?) */ \
	{ write_pixel_lm(x, y - 1, s, l); write_pixel_lm(x, y, s, l); write_pixel_lm(x, y + 1, s, l); }

#define	DRAW_ENDCAP_VLINE(e, x, y, s, f, l) \
	if((e) == ENDCAP_ROUND) /* single pixel endcap */ \
	{ write_pixel_lm(x, y, f, l); } \
	else if((e) == ENDCAP_FLAT) /* flat endcap: FIXME, quicker to draw a horizontal line(?) */ \
	{ write_pixel_lm(x - 1, y, s, l); write_pixel_lm(x, y, s, l); write_pixel_lm(x + 1, y, s, l); }

// Font flags.
#define	FONT_BOLD		1		// bold text (no outline)
#define	FONT_INVERT		2		// invert: border white, inside black

// Text alignments.
#define	TEXT_VA_TOP		0
#define	TEXT_VA_MIDDLE	1
#define	TEXT_VA_BOTTOM	2
#define	TEXT_HA_LEFT	0
#define	TEXT_HA_CENTER	1
#define	TEXT_HA_RIGHT	2

// Text dimension structures.
struct FontDimensions
{
	int width, height
};

// Macro to swap buffers given a temporary pointer.
#define	SWAP_BUFFS(tmp, a, b) { tmp = a; a = b; b = tmp; }

// Macro to swap two variables using XOR swap.
#define SWAP(a, b) { a ^= b; b ^= a; a ^= b; }

// Macros for writing pixels in a midpoint circle algorithm.
#define CIRCLE_PLOT_8(buff, cx, cy, x, y, mode) \
	CIRCLE_PLOT_4(buff, cx, cy, x, y, mode); \
	if((x) != (y)) CIRCLE_PLOT_4(buff, cx, cy, y, x, mode);

#define CIRCLE_PLOT_4(buff, cx, cy, x, y, mode) \
	write_pixel(buff, (cx) + (x), (cy) + (y), mode); \
	write_pixel(buff, (cx) - (x), (cy) + (y), mode); \
	write_pixel(buff, (cx) + (x), (cy) - (y), mode); \
	write_pixel(buff, (cx) - (x), (cy) - (y), mode);

// Check if coordinates are valid. If not, return.
#define CHECK_COORDS(x, y) if(x < 0 || x >= DISP_WIDTH || y < 0 || y >= DISP_HEIGHT) return;
#define CHECK_COORD_X(x) if(x < 0 || x >= DISP_WIDTH) return;
#define CHECK_COORD_Y(y) if(y < 0 || y >= DISP_HEIGHT) return;

// Clip coordinates out of range.
#define CLIP_COORD_X(x) { x = MAX(0, MIN(x, DISP_WIDTH)); }
#define CLIP_COORD_Y(y) { y = MAX(0, MIN(y, DISP_HEIGHT)); }
#define CLIP_COORDS(x, y) { CLIP_COORD_X(x); CLIP_COORD_Y(y); }

// Externs for graphics buffers pointers. (Direct access to buffers typically
// not allowed.)
extern uint16_t *draw_buffer_level;
extern uint16_t *draw_buffer_mask;
extern uint16_t *disp_buffer_level;
extern uint16_t *disp_buffer_mask;

// ** Function prototypes. **
// Buffer management.
void init_gfx();
void swap_buffers();
void fill_buffer(uint16_t *buff, uint16_t word);
void fill_buffer_rand(uint16_t *buff);
// Basic primitives.
void write_pixel(uint16_t *buff, unsigned int x, unsigned int y, int mode);
void write_pixel_lm(unsigned int x, unsigned int y, int mmode, int lmode);
//void write_pixel_outlined(uint16_t *buff, unsigned int x, unsigned int y, int btype, int mmode, int mode);
// Shape primitives.
void write_filled_rectangle(uint16_t *buff, unsigned int x, unsigned int y, unsigned int width, unsigned int height, int mode);
void write_filled_rectangle_lm(unsigned int x, unsigned int y, unsigned int width, unsigned int height, int lmode, int mmode);
void write_circle(uint16_t *buff, unsigned int x, unsigned int y, unsigned int r, unsigned int dashp, int mode);
void write_circle_outlined(unsigned int cx, unsigned int cy, unsigned int r, unsigned int dashp, int bmode, int mode, int mmode);
void write_circle_filled(uint16_t *buff, unsigned int x, unsigned int y, unsigned int r, int mode);
// Line primitives.
void write_hline(uint16_t *buff, unsigned int x0, unsigned int x1, unsigned int y, int mode);
void write_hline_lm(unsigned int x0, unsigned int x1, unsigned int y, int lmode, int mmode);
void write_hline_outlined(unsigned int x0, unsigned int x1, unsigned int y, int endcap0, int endcap1, int mode, int mmode);
void write_vline(uint16_t *buff, unsigned int x, unsigned int y0, unsigned int y1, int mode);
void write_vline_lm(unsigned int x, unsigned int y0, unsigned int y1, int lmode, int mmode);
void write_vline_outlined(unsigned int x, unsigned int y0, unsigned int y1, int endcap0, int endcap1, int mode, int mmode);
void write_line(uint16_t *buff, unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, int mode);
void write_line_outlined(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, int mmode, int mode);
void write_rectangle_outlined(unsigned int x, unsigned int y, int width, int height, int mode, int mmode);
// Text functions.
void write_word_misaligned(uint16_t *buff, uint16_t word, unsigned int addr, unsigned int xoff, int mode);
void write_word_misaligned_lm(uint16_t wordl, uint16_t wordm, unsigned int addr, unsigned int xoff, int lmode, int mmode);
int fetch_font_info(char ch, int font, struct FontEntry *font_info, char *lookup);
void write_char(char ch, unsigned int x, unsigned int y, int flags, int font);
void calc_text_dimensions(char *str, struct FontEntry font, int xs, int ys, struct FontDimensions *dim);
void write_string(char *str, unsigned int x, unsigned int y, unsigned int xs, unsigned int ys, int va, int ha, int flags, int font);

#endif	// GFX_H