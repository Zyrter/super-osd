/**
 * Widgets for the Head Up Display.
 * These include compasses, altimeters, and variometers.
 */

#include "osd.h"
#include "osdadd.h"
#include <stdio.h>

struct TextSize tsize;

void format_time(long int time, char *buff)
{
	/* This doesn't use sprintf, which makes it fast and compact. */
	time %= 360000;				 // wrap around at 99 hours, 59 minutes, 59 seconds.
	int seconds = time % 60;
	int minutes = (time / 60) % 60;
	int hours = time / 3600;
	memset(buff, 0x00, 9); // 8 characters required + 1 NUL
	buff[0] = '0' + (hours / 10);
	buff[1] = '0' + (hours % 10);
	buff[2] = ':';
	buff[3] = '0' + (minutes / 10);
	buff[4] = '0' + (minutes % 10);
	buff[5] = ':';
	buff[6] = '0' + (seconds / 10);
	buff[7] = '0' + (seconds % 10);
	//buff[8] = '\0';
}

/**
 * Implementations of itoa and reverse.
 * http://en.wikipedia.org/wiki/Itoa
 */
/* itoa: convert n to characters in s */
void my_itoa(long int n, char s[])
{
	int i, sign;

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
}

/* reverse: reverse string s in place */
void my_reverse(char s[])
{
	int i, j;
	char c;

	for (i = 0, j = strlen(s)-1; i<j; i++, j--) 
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void hud_draw_lin_compass(int cx, int cy, int tick_maj, int tick_min, int range, int heading)
{
	// Fix heading, if necessary.
	heading %= 360;
	// Draw current heading. Faster than itoa, because we know it's going to be
	// three digits long; it also makes it possible to pad easily.
	buff[0] = '0' + (heading / 100);
	buff[1] = '0' + ((heading % 100) / 10);
	buff[2] = '0' + (heading % 10);
	buff[3] = '\0';
	draw_text_aligned(buff, cx, cy - 2, HALIGN_CENTER, VALIGN_BOTTOM, 1, 0, 0);
	// From -(range / 2) to +(range / 2), draw each tick
	// and draw the heading markers.
	int r = -range / 2;
	for(; r < (range / 2); r++)
	{
		int x = cx + r; 					// TODO: we could implement a scale factor here
		int rr = (heading + r + 360) % 360;	// normalise values; this makes code simpler
		
		if(rr == 0 || rr == 90 || rr == 180 || rr == 270)
		{
			dvline(x, cy + 4, cy, 1);
			// Cardinal direction?
			buff[0] = '?';
			switch(rr)
			{
				case 0: 	buff[0] = 'N'; break;
				case 90: 	buff[0] = 'E'; break;
				case 180: 	buff[0] = 'S'; break;
				case 270: 	buff[0] = 'W'; break;
			}
			buff[1] = '\0';
			draw_text_aligned(buff, x, cy + 6, HALIGN_CENTER, VALIGN_TOP, 1, 0, 0);
		}
		else if(rr % tick_maj == 0)
		{
			dvline(x, cy + 4, cy, 1);
			// Calculate heading string, and output it.
			buff[0] = '0' + (rr / 100);
			buff[1] = '0' + ((rr / 10) % 10);
			buff[2] = '\0';
			draw_text_aligned(buff, x, cy + 6, HALIGN_CENTER, VALIGN_TOP, 1, 0, 0);
		}
		else if(rr % tick_min == 0)
		{
			dvline(x, cy + 2, cy, 1);
		}
	}
	// Get font size. This is used for the next part.
	textsize(0, &tsize);
	// Clean up the edges by blocking off incomplete heading numbers.
	dfrect(cx - (range / 2) - tsize.width, cy, tsize.width * 2, tsize.height * 2, 0);
	dfrect(cx + (range / 2) - tsize.width, cy, tsize.width * 2, tsize.height * 2, 0);
}

void hud_draw_airspeed_indicator(int cx, int cy, int tick_maj, int tick_min, int range, int airspeed)
{
	struct TextBBox bbox;
	// Draw ticks and values.
	int r = -range / 2;
	for(; r < (range / 2); r++)
	{
		int y = cy - r; 					// TODO: we could implement a scale factor here
		int rr = airspeed + r;
		
		if(rr >= 0)
		{
			if(rr % tick_maj == 0)
			{
				my_itoa(rr, buff);
				draw_text_aligned(buff, cx - 15, y, HALIGN_RIGHT, VALIGN_MIDDLE, 1, 0, 0);
				dhline(cx - 3, cx + 6, y, 1);
			}
			else if(rr % tick_min == 0)
			{
				dhline(cx - 3, cx + 3, y, 1);
			}
		}
	}
	// Convert airspeed to string and bbox. Make the first character a space,
	// this helps with the next calculations.
	buff[0] = ' ';
	my_itoa(airspeed, buff + 1);
	bbox_text_aligned(buff, cx - 15, cy, HALIGN_RIGHT, VALIGN_MIDDLE, 1, 0, &bbox);
	// Fill a rectangle behind the text, so the text underneath doesn't show.
	dfrect(bbox.x - 1, bbox.y - 1, bbox.width + 1, bbox.height + 1, 1);
	draw_text_bbox(buff, bbox, 1, 0, 1);
	// Draw a box around this text.
	draw_rect_outline(bbox.x - 2, bbox.y - 2, bbox.width + 2, bbox.height + 3, 1);
	// Clear the edge of the rect. HACK; probably would be better to only draw 3 lines.
	dvline(bbox.x + bbox.width, bbox.y, bbox.y + bbox.height, 0);
	// Draw an arrow tapering off. Using dvline.
	int x = bbox.x + bbox.width;
	int y = 0;
	for(; y <= ((bbox.height / 2) + 2); y++)
	{
		dvline(x, bbox.y + y - 2, bbox.y + bbox.height - y + 1, 1);
		x++;
	}
	//draw_line(bbox.x + bbox.width, bbox.y - 1, bbox.x + bbox.width + bbox.height + 1, bbox.y + (bbox.height / 2), 1);
	//draw_line(bbox.x + bbox.width, bbox.y + bbox.height, bbox.x + bbox.width + bbox.height + 1, bbox.y + (bbox.height / 2), 1);
	// Get font size. This is used for the next part.
	textsize(0, &tsize);
	// Cut off the bottom and top.
	dfrect(bbox.x, cy + (range / 2), bbox.width + 25, tsize.height, 0); // NOTE: constant 25 works well
	dfrect(bbox.x, cy - (range / 2), bbox.width + 25, tsize.height, 0);
}

void hud_draw_altitude_indicator(int cx, int cy, int tick_maj, int tick_min, int range, int altitude)
{
	struct TextBBox bbox;
	// Draw ticks and values.
	int r = -range / 2;
	for(; r < (range / 2); r++)
	{
		int y = cy - r; 					// TODO: we could implement a scale factor here
		int rr = altitude + r;
		
		if(rr % tick_maj == 0)
		{
			my_itoa(rr, buff);
			draw_text_aligned(buff, cx + 15, y, HALIGN_LEFT, VALIGN_MIDDLE, 1, 0, 0);
			dhline(cx + 3, cx - 6, y, 1);
		}
		else if(rr % tick_min == 0)
		{
			dhline(cx + 3, cx - 3, y, 1);
		}
	}
	// First, clear the buffer.
	memset(buff, 0x00, 50);
	// Convert altitude to string and bbox. Make the last character a space,
	// this helps with the next calculations.
	my_itoa(altitude, buff);
	buff[strlen(buff)] = ' ';
	bbox_text_aligned(buff, cx + 15, cy, HALIGN_LEFT, VALIGN_MIDDLE, 1, 0, &bbox);
	// Fill a rectangle behind the text, so the text underneath doesn't show.
	dfrect(bbox.x - 1, bbox.y - 1, bbox.width + 1, bbox.height + 1, 1);
	draw_text_bbox(buff, bbox, 1, 0, 1);
	// Draw a box around this text.
	draw_rect_outline(bbox.x - 2, bbox.y - 2, bbox.width + 2, bbox.height + 3, 1);
	// Clear the edge of the rect. HACK; probably would be better to only draw 3 lines
	// around the rectangle.
	dvline(bbox.x - 2, bbox.y - 2, bbox.y + bbox.height + 2, 0);
	// Draw an arrow tapering off. Using dvline.
	int x = bbox.x - 1;
	int y = 0;
	for(; y <= ((bbox.height / 2) + 2); y++)
	{
		dvline(x, bbox.y + y - 2, bbox.y + bbox.height - y + 1, 1);
		x--;
	}
	//draw_line(bbox.x + bbox.width, bbox.y - 1, bbox.x + bbox.width + bbox.height + 1, bbox.y + (bbox.height / 2), 1);
	//draw_line(bbox.x + bbox.width, bbox.y + bbox.height, bbox.x + bbox.width + bbox.height + 1, bbox.y + (bbox.height / 2), 1);
	// Get font size. This is used for the next part.
	textsize(0, &tsize);
	// Cut off the bottom and top.
	dfrect(cx - 15, cy + (range / 2), bbox.width + 35, tsize.height, 0); // NOTE: constants 35 & 15 work well
	dfrect(cx - 15, cy - (range / 2), bbox.width + 35, tsize.height, 0);
}