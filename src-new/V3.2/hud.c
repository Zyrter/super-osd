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
 * hud_draw_compass: Draw a compass.
 * 
 * @param	v				value for the compass
 * @param	range			range about value to display (+/- range/2 each direction)
 * @param	width			length in pixels
 * @param	x				x displacement (typ. half display width)
 * @param	y				y displacement (typ. bottom of display)
 * @param	mintick_step	how often a minor tick is shown
 * @param	majtick_step	how often a major tick (heading "xx") is shown
 * @param	mintick_len		minor tick length
 * @param	majtick_len		major tick length
 * @param	flags			special flags (see hud.h.)
 */
void hud_draw_linear_compass(int v, int range, int width, int x, int y, int mintick_step, int majtick_step, int mintick_len, int majtick_len, int flags)
{
	v %= 360; // wrap, just in case.
	struct FontEntry font_info;
	int majtick_start = 0, majtick_end = 0, mintick_start = 0, mintick_end = 0, textoffset = 0;
	char headingstr[4];
	majtick_start = y;
	majtick_end = y - majtick_len;
	mintick_start = y;
	mintick_end = y - mintick_len;
	textoffset = 8;
	int r, style, rr, rv, xs;
	int range_2 = range / 2;
	for(r = -range_2; r <= +range_2; r++)
	{
		style = 0;
		rr = (v + r + 360) % 360; // normalise range for modulo, add to move compass track
		rv = -rr + range_2; // for number display
		if(rr % majtick_step == 0)
			style = 1; // major tick
		else if(rr % mintick_step == 0)
			style = 2; // minor tick
		if(style)
		{
			// Calculate x position.
			xs = ((long int)(r * width) / (long int)range) + x; 
			// Draw it.
			if(style == 1)
			{
				write_vline_outlined(xs, majtick_start, majtick_end, 2, 2, 0, 1);
				// Draw heading above this tick.
				// If it's not one of north, south, east, west, draw the heading. 
				// Otherwise, draw one of the identifiers.
				if(rr % 90 != 0)
				{
					// We abbreviate heading to two digits. This has the side effect of being easy to compute.
					headingstr[0] = '0' + (rr / 100);
					headingstr[1] = '0' + ((rr / 10) % 10);
					headingstr[2] = 0; 
					headingstr[3] = 0; // nul to terminate
				}
				else
				{
					switch(rr)
					{
						case 0:   headingstr[0] = 'N'; break;
						case 90:  headingstr[0] = 'E'; break;
						case 180: headingstr[0] = 'S'; break;
						case 270: headingstr[0] = 'W'; break;
					}
					headingstr[1] = 0;
					headingstr[2] = 0;
					headingstr[3] = 0;
				}
				// +1 fudge...!
				write_string(headingstr, xs + 1, majtick_start + textoffset, 1, 0, TEXT_VA_MIDDLE, TEXT_HA_CENTER, 0, 1);
			}
			else if(style == 2)
				write_vline_outlined(xs, mintick_start, mintick_end, 2, 2, 0, 1);
		}
	}
	// Then, draw a rectangle with the present heading in it.
	// We want to cover up any other markers on the bottom.
	// First compute font size.
	fetch_font_info(1, 1, &font_info, NULL);
	int text_width = (font_info.width + 1) * 3;
	int rect_width = text_width + 2;
	write_filled_rectangle_lm(x - (rect_width / 2), majtick_start + 2, rect_width, font_info.height + 2, 0, 1);
	write_rectangle_outlined(x - (rect_width / 2), majtick_start + 2, rect_width, font_info.height + 2, 0, 1);
	headingstr[0] = '0' + (v / 100);
	headingstr[1] = '0' + ((v / 10) % 10);
	headingstr[2] = '0' + (v % 10);
	headingstr[3] = 0;
	write_string(headingstr, x + 1, majtick_start + textoffset, 1, 0, TEXT_VA_MIDDLE, TEXT_HA_CENTER, 1, 1);
}

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
 * @param	mintick_len		minor tick length
 * @param	majtick_len		major tick length
 * @param	max_val			maximum expected value (used to compute size of arrow ticker)
 * @param	flags			special flags (see hud.h.)
 */
void hud_draw_vertical_scale(int v, int range, int halign, int x, int y, int height, int mintick_step, int majtick_step, int mintick_len, int majtick_len, int boundtick_len, int max_val, int flags)
{
	char temp[15], temp2[15];
	struct FontEntry font_info;
	struct FontDimensions dim;
	// Halign should be in a small span.
	MY_ASSERT(halign >= -1 && halign <= 1);
	// Compute the position of the elements.
	int majtick_start = 0, majtick_end = 0, mintick_start = 0, mintick_end = 0, boundtick_start = 0, boundtick_end = 0;
	if(halign == -1)
	{
		majtick_start = x;
		majtick_end = x + majtick_len;
		mintick_start = x;
		mintick_end = x + mintick_len;
		boundtick_start = x;
		boundtick_end = x + boundtick_len;
	}
	else if(halign == +1)
	{
		majtick_start = DISP_WIDTH - x - 1;
		majtick_end = DISP_WIDTH - x - majtick_len - 1;
		mintick_start = DISP_WIDTH - x - 1;
		mintick_end = DISP_WIDTH - x - mintick_len - 1;
		boundtick_start = DISP_WIDTH - x - 1;
		boundtick_end = DISP_WIDTH - x - boundtick_len - 1;
	}
	// Retrieve width of large font (font #0); from this calculate the x spacing.
	fetch_font_info(0, 0, &font_info, NULL);
	int arrow_len = (font_info.height / 2) + 1;		// FIXME, font info being loaded correctly??
	int text_x_spacing = arrow_len;
	int max_text_y = 0, text_length = 0;
	int small_font_char_width = font_info.width + 1; // +1 for horizontal spacing = 1
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
		if(rr % majtick_step == 0)
			style = 1; // major tick
		else if(rr % mintick_step == 0)
			style = 2; // minor tick
		else
			style = 0;
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
				text_length = (strlen(temp) + 1) * small_font_char_width; // add 1 for margin
				if(text_length > max_text_y)
					max_text_y = text_length;
				if(halign == -1)
					write_string(temp, majtick_end + text_x_spacing, ys, 1, 0, TEXT_VA_MIDDLE, TEXT_HA_LEFT, 0, 1);
				else
					write_string(temp, majtick_end - text_x_spacing + 1, ys, 1, 0, TEXT_VA_MIDDLE, TEXT_HA_RIGHT, 0, 1);
			}
			else if(style == 2)
				write_hline_outlined(mintick_start, mintick_end, ys, 2, 2, 0, 1);
		}
	}
	// Generate the string for the value, as well as calculating its dimensions.
	memset(temp, ' ', 10);
	my_itoa(v, temp);
	// TODO: add auto-sizing.
	calc_text_dimensions(temp, font_info, 1, 0, &dim);
	int xx = 0, i = 0;
	if(halign == -1)
		xx = majtick_end + text_x_spacing;
	else
		xx = majtick_end - text_x_spacing;
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
	// Then, add a slow cut off on the edges, so the text doesn't sharply
	// disappear. We simply clear the areas above and below the ticker, and we
	// use little markers on the edges.
	if(halign == -1)
	{
		write_filled_rectangle_lm(majtick_end + text_x_spacing, y + (height / 2) - (font_info.height / 2), max_text_y - boundtick_start, font_info.height, 0, 0);
		write_filled_rectangle_lm(majtick_end + text_x_spacing, y - (height / 2) - (font_info.height / 2), max_text_y - boundtick_start, font_info.height, 0, 0);	
	}
	else
	{
		write_filled_rectangle_lm(majtick_end - text_x_spacing - max_text_y, y + (height / 2) - (font_info.height / 2), max_text_y, font_info.height, 0, 0);
		write_filled_rectangle_lm(majtick_end - text_x_spacing - max_text_y, y - (height / 2) - (font_info.height / 2), max_text_y, font_info.height, 0, 0);
	}
	write_hline_outlined(boundtick_start, boundtick_end, y + (height / 2), 2, 2, 0, 1);
	write_hline_outlined(boundtick_start, boundtick_end, y - (height / 2), 2, 2, 0, 1);
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
	int alt = 0, airspeed = 0, heading = 0, aira = 1, alta = 1, hdga = 1;
	int oldalt = 0, oldas = 0;
	int ctr = 0, ctr2 = 0, fps = 0;
	long int last_time = 0;
	char buff[20];
	use_vsync = 1;
	while(1)
	{
		// We run the HUD at 1/5th camera field rate, so we have time to fit a lot of graphics in.
		while(tv_field % 5 != 0);
		fill_buffer(draw_buffer_mask, 0x0000);
		fill_buffer(draw_buffer_level, 0x0000);
		// Calculate FPS.
		ctr++;
		if(tv_time != last_time)
		{
			fps = ctr;
			ctr = 0;
			last_time = tv_time;
		}
		// Draw airspeed (left side.)
		hud_draw_vertical_scale(airspeed, 100, -1, 2, (DISP_HEIGHT / 2) + 10, 120, 5, 20, 7, 12, 15, 10000, HUD_VSCALE_FLAG_NO_NEGATIVE);
		// Draw altimeter (right side.)
		hud_draw_vertical_scale(alt, 200, +1, 2, (DISP_HEIGHT / 2) + 10, 120, 20, 100, 7, 12, 15, 500, 0);
		// Draw compass.
		hud_draw_linear_compass(heading, 150, 120, DISP_WIDTH / 2, DISP_HEIGHT - 20, 15, 30, 7, 12, 0);
		// TEST: draw lines on display every 10 pixels.
		//write_hline_lm(0, DISP_WIDTH, 0, 1, 1);
		/*
		write_hline_lm(0, DISP_WIDTH, 10, 1, 1);
		write_hline_lm(0, DISP_WIDTH, 20, 1, 1);
		write_hline_lm(0, DISP_WIDTH, 30, 1, 1);
		write_hline_lm(0, DISP_WIDTH, 40, 1, 1);
		
		write_hline_lm(0, DISP_WIDTH, 50, 1, 1);
		write_hline_lm(0, DISP_WIDTH, 60, 1, 1);
		write_hline_lm(0, DISP_WIDTH, 70, 1, 1);
		write_hline_lm(0, DISP_WIDTH, 80, 1, 1);
		write_hline_lm(0, DISP_WIDTH, 90, 1, 1);
		
		write_hline_lm(0, DISP_WIDTH, 100, 1, 1);
		write_hline_lm(0, DISP_WIDTH, 110, 1, 1);
		write_hline_lm(0, DISP_WIDTH, 120, 1, 1);
		write_hline_lm(0, DISP_WIDTH, 130, 1, 1);
		write_hline_lm(0, DISP_WIDTH, 140, 1, 1);
		
		write_hline_lm(0, DISP_WIDTH, 150, 1, 1);
		write_hline_lm(0, DISP_WIDTH, 160, 1, 1);
		write_hline_lm(0, DISP_WIDTH, 170, 1, 1);
		write_hline_lm(0, DISP_WIDTH, 180, 1, 1);
		write_hline_lm(0, DISP_WIDTH, 190, 1, 1);
		
		write_hline_lm(0, DISP_WIDTH, 200, 1, 1);
		write_hline_lm(0, DISP_WIDTH, 208, 1, 1);
		*/
		// Test warning.
		/*
		if((tv_field / 25) % 2 == 0)
		{
			write_string("BATTERY", disp_width / 2, (disp_height / 2) - 80, 1, 0, TEXT_VA_MIDDLE, TEXT_HA_CENTER, 0, 0);
			write_string("LOW!", disp_width / 2, (disp_height / 2) - 66, 1, 0, TEXT_VA_MIDDLE, TEXT_HA_CENTER, 0, 0);
		}
		*/
		// Test lines.
		//write_line_outlined(10, 10, 50, 80, 0, 0, 0, 1);
		//write_line_outlined(90, 15, 50, 80, 0, 0, 0, 1);
		//write_line_outlined(180, 100, 190, 150, 0, 0, 0, 1);
		//write_line_lm(0, 0, 50, airspeed * 2, 1, 1);
		//write_line_lm(20, 20, 200, airspeed / 10, 1, 1);
		// Increment alt/airspeed.
		oldalt = alt;
		alt += alta;
		if(alt > 2000)  alta = -1;
		if(alt < -2000) alta = +1;
		oldas = airspeed;
		airspeed += aira;
		if(airspeed > 100) aira = -1;
		if(airspeed <  10) aira = +1;
		heading += hdga;
		heading %= 360;
		swap_buffers();
	}
}
