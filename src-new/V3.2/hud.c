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
#include "osd.h"

extern unsigned int tv_field;
extern long int tv_time;

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
 * @param	mintick_step	how often a minor tick is shown
 * @param	majtick_step	how often a major tick is shown
 * @param	majtick_len		major tick length
 * @param	mintick_len		minor tick length
 * @param	max_val			maximum expected value (used to compute size of arrow ticker)
 * @param	flags			special flags (see hud.h.)
 */
void hud_draw_vertical_scale(int v, int range, int halign, int x, int y, int height, int mintick_step, int majtick_step, int majtick_len, int mintick_len, int max_val, int flags)
{
	char temp[15], temp2[15];
	struct FontEntry font_info;
	struct FontDimensions dim;
	// Halign should be in a small span.
	MY_ASSERT(halign >= -1 && halign <= 1);
	// Compute the position of the elements.
	int majtick_start = 0, majtick_end = 0, mintick_start = 0, mintick_end = 0;
	if(halign == -1)
	{
		majtick_start = x;
		majtick_end = x + majtick_len;
		mintick_start = x;
		mintick_end = x + mintick_len;
	}
	else if(halign == +1)
	{
		majtick_start = DISP_WIDTH - x - 1;
		majtick_end = DISP_WIDTH - x - majtick_len - 1;
		mintick_start = DISP_WIDTH - x - 1;
		mintick_end = DISP_WIDTH - x - mintick_len - 1;
	}
	// Retrieve width of large font (font #0); from this calculate the x spacing.
	fetch_font_info(0, 0, &font_info, NULL);
	int arrow_len = (font_info.height / 2) + 1;		// FIXME, font info being loaded correctly??
	int text_x_spacing = arrow_len * 2;
	// For -(range / 2) to +(range / 2), draw the scale.
	int range_2 = range / 2, height_2 = height / 2;
	int calc_ys = 0, r = 0, rr = 0, rv = 0, ys = 0, style = 0;
	// Iterate through each step.
	for(r = -range_2; r <= +range_2; r++)
	{
		style = 0;
		rr = r + range_2 - v; // normalise range for modulo, subtract value to move ticker tape
		rv = -rr + range_2; // for number display
		if(flags & HUD_VSCALE_FLAG_NO_NEGATIVE)
			rr += majtick_step / 2;
		// Negative not allowed? (for example, airspeed meter.) If so, skip modulo calculations.
		if(rr % majtick_step == 0)
			style = 1; // major tick
		else if(rr % mintick_step == 0)
			style = 2; // minor tick
		if(flags & HUD_VSCALE_FLAG_NO_NEGATIVE && rv < 0)
			continue;
		if(style)
		{
			// Calculate y position.
			ys = ((long int)(r * height) / (long int)range) + y; 
			//sprintf(temp, "ys=%d", ys);
			//con_puts(temp, 0);
			// Depending on style, draw a minor or a major tick.
			if(style == 1)
			{
				write_hline_outlined(majtick_start, majtick_end, ys, 2, 2, 0, 1);
				memset(temp, ' ', 10);
				my_itoa(rv, temp);
				if(halign == -1)
					write_string(temp, majtick_end + text_x_spacing, ys + 1, 1, 0, TEXT_VA_MIDDLE, TEXT_HA_LEFT, 0, 1);
				else
					write_string(temp, majtick_end - text_x_spacing + 1, ys + 1, 1, 0, TEXT_VA_MIDDLE, TEXT_HA_RIGHT, 0, 1);
			}
			else if(style == 2)
				write_hline_outlined(mintick_start, mintick_end, ys, 2, 2, 0, 1);
		}
	}
	// Generate the string for the value, as well as calculating its dimensions.
	write_hline_outlined(majtick_start, majtick_end, ys, 2, 2, 0, 1);
	memset(temp, ' ', 10);
	my_itoa(v, temp);
	// TODO: add auto-sizing.
	calc_text_dimensions(temp, font_info, 1, 0, &dim);
	int xx = 0, i = 0;
	if(halign == -1)
		xx = majtick_end + text_x_spacing;
	else
		xx = majtick_end - text_x_spacing + 1;
	// Draw an arrow from the number to the point.
	for(i = 0; i < arrow_len; i++)
	{
		if(halign == -1)
		{
			write_pixel_lm(xx - arrow_len + i, y - i - 1, 1, 1);
			write_pixel_lm(xx - arrow_len + i, y + i - 1, 1, 1);
			write_hline_lm(xx + dim.width - 1, xx - arrow_len + i + 1, y - i - 1, 0, 1);
			write_hline_lm(xx + dim.width - 1, xx - arrow_len + i + 1, y + i - 1, 0, 1);
		}
		else
		{
			write_pixel_lm(xx + arrow_len - i, y - i - 1, 1, 1);
			write_pixel_lm(xx + arrow_len - i, y + i - 1, 1, 1);
			write_hline_lm(xx - dim.width - 1, xx + arrow_len - i - 1, y - i - 1, 0, 1);
			write_hline_lm(xx - dim.width - 1, xx + arrow_len - i - 1, y + i - 1, 0, 1);
		}
		// FIXME
		// write_hline_lm(xx - dim.width - 1, xx + (arrow_len - i), y - i - 1, 1, 1);
		// write_hline_lm(xx - dim.width - 1, xx + (arrow_len - i), y + i - 1, 1, 1);
	}
	if(halign == -1)
	{
		write_hline_lm(xx, xx + dim.width - 1, y - arrow_len, 1, 1);
		write_hline_lm(xx, xx + dim.width - 1, y + arrow_len - 2, 1, 1);
		write_vline_lm(xx + dim.width - 1, y - arrow_len, y + arrow_len - 2, 1, 1);
	}
	else
	{
		write_hline_lm(xx, xx - dim.width - 1, y - arrow_len, 1, 1);
		write_hline_lm(xx, xx - dim.width - 1, y + arrow_len - 2, 1, 1);
		write_vline_lm(xx - dim.width - 1, y - arrow_len, y + arrow_len - 2, 1, 1);
	}
	// Draw the text.
	if(halign == -1)
		write_string(temp, xx, y, 1, 0, TEXT_VA_MIDDLE, TEXT_HA_LEFT, 0, 0);
	else
		write_string(temp, xx, y, 1, 0, TEXT_VA_MIDDLE, TEXT_HA_RIGHT, 0, 0);
	
}

/**
 * hud_demo: Draw a demonstration HUD.
 *
 * TODO: add support for auto-clearing the previous HUD data
 * instead of doing a complete display sweep. Leave intact
 * constant items.
 */
void hud_demo()
{
	int alt = 0, airspeed = 0, aira = 1, alta = 1;
	int ctr = 0, ctr2 = 0, fps = 0;
	long int last_time = 0;
	char buff[20];
	while(1)
	{
		// We run the HUD at 1/5th camera field rate, to improve the graphic quality of it.
		while(tv_field % 5 != 0);
		fill_buffer(draw_buffer_mask, 0x0000);
		fill_buffer(draw_buffer_level, 0x0000);
		// Draw/update FPS.
		ctr++;
		if(tv_time != last_time)
		{
			fps = ctr;
			ctr = 0;
			last_time = tv_time;
		}
		memset(buff, 0, 10);
		//strcat(buff, "FPS:");
		my_itoa(fps, buff + strlen(buff));
		write_string(buff, 0, 0, 1, 0, TEXT_VA_TOP, TEXT_HA_LEFT, 0, 1);
		//gfx_align_test();
		//write_string("HAI WORLD", 0, 0, DISP_WIDTH - 1, 0, TEXT_VA_TOP, TEXT_HA_RIGHT, 0, 1);
		// Draw airspeed (left side.)
		hud_draw_vertical_scale(airspeed, 100, -1, 2, (DISP_HEIGHT / 2) + 7, 160, 5, 20, 12, 7, 10000, HUD_VSCALE_FLAG_NO_NEGATIVE);
		// Draw altimeter (right side.)
		hud_draw_vertical_scale(alt, 200, +1, 2, (DISP_HEIGHT / 2) + 7, 160, 20, 100, 12, 7, 500, 0);
		// Increment alt/airspeed.
		if(ctr2 % 2 == 0)
		{
			alt += alta;
			if(alt > 2000) alta = -1;
			if(alt < -200) alta = +1;
			airspeed += aira;
			if(airspeed > 100) aira = -1;
			if(airspeed <  10) aira = +1;
		}
		ctr2++;
		swap_buffers();
	}
}
