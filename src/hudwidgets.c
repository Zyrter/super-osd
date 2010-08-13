/**
 * Widgets for the Head Up Display.
 * These include compasses, altimeters, and variometers.
 */

#include "osd.h"
#include "osdadd.h"
#include <stdio.h>

char buff[50];
	
void hud_draw_lin_compass(int cx, int cy, int tick_maj, int tick_min, int range, int heading)
{
	// From -(range / 2) to +(range / 2), draw each tick
	// and draw the heading markers.
	int r = -range / 2;
	for(; r < (range / 2); r++)
	{
		int x = r + cx; 			// TODO: we could implement a scale factor here
		int rr = (r + 360) % 360;	// normalise values; this makes code simpler
		int curr_head = heading + r;
		
		if(rr % tick_maj == 0)
		{
			//dvline(x, cy + 4, cy, 1);
			sprintf(buff, "%d", curr_head);
			//draw_text_aligned(buff, x, cy + 6, HALIGN_CENTER, VALIGN_TOP, 1, 0, 0);
		}
		else if(rr % tick_min == 0)
		{
			//dvline(x, cy + 2, cy, 1);
		}
	}
	r += 2;
	r *= 4;
}