/**
 * This implements several demo.
 *
 * It is written in C because that makes many parts easier.
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "demo.h"
#include "osd.h"
#include "osdadd.h"
#include "c_images.h"

/**
 * Triangle wave. The input is 0x0000 to 0xffff
 * and the output is from -range/20 to +range/2.
 */
int triangle(int x, unsigned int range)
{
	return abs(x - (range + 1)) - (range / 2);
}

void demo_intro_text1()
{
	int i, j, k;
	for(j = 0; j < 100; j++)
	{
		for(i = 0; i < 21; i++)
		{
			k = triangle(i % 21, 10) + 5; 
			fill_mem(0xffff);
			drawstr("Super OSD is a powerful", 5, 5, 1, 0, k);
			k = triangle((i + 1) % 21, 10) + 5;
			drawstr("open source on screen display", 5, 11, 1, 0, k);
			k = triangle((i + 2) % 21, 10) + 5;
			drawstr("for PAL and NTSC video signals.", 5, 17, 1, 0, k);
			k = triangle((i + 3) % 21, 10) + 5;
			drawstr("It supports:", 5, 29, 1, 0, k);
			k = triangle((i + 4) % 21, 10) + 5;
			drawstr(" - 256x192 pixels", 5, 35, 1, 0, k);
			k = triangle((i + 5) % 21, 10) + 5;
			drawstr(" - Double buffering (WIP)", 5, 41, 1, 0, k);
			k = triangle((i + 6) % 21, 10) + 5;
			drawstr(" - Text (5x5 as shown here)", 5, 47, 1, 0, k);
			k = triangle((i + 6) % 21, 10) + 5;
			drawstr(" - Graphical primitives", 5, 53, 1, 0, k);
			k = triangle((i + 7) % 21, 10) + 5;
			drawstr("   (Rectangles, lines and circles)", 5, 59, 1, 0, k);
			k = triangle((i + 8) % 21, 10) + 5;
			drawstr(" - Accelerated horizontal and vertical lines", 5, 65, 1, 0, k);
			k = triangle((i + 9) % 21, 10) + 5;
			drawstr(" - Fast software OSD in assembly language", 5, 71, 1, 0, k);
			k = triangle((i + 10) % 21, 10) + 5;
			drawstr(" - Interrupt driven", 5, 77, 1, 0, k);
			//draw_fps();
			update_fps();
			BDISP = 1 - BDISP;
			BDRAW = 1 - BDRAW;
			delay(20);
		}
	}
}

void demo_intro_text2()
{
	char buff[50];
    int y = 5;
    drawbm2(logo_small);
    drawstr("S/W v2.1-alpha", 100, 150, 0, 0, 1);
    
    drawstr("Super OSD!", 5, y, 0, 0, 1); y += 12;
    	
    drawstr("What is Super OSD?", 5, y, 0, 0, 1); y += 12;
    
    drawstr("Super OSD is a free, open-source (GPLv2)", 5, y, 0, 0, 1); y += 6;
    drawstr("graphical on screen display for PAL and", 5, y, 0, 0, 1); y += 6;
    drawstr("NTSC video signals. It is primarily", 5, y, 0, 0, 1); y += 6;
    drawstr("designed as an alternative to current", 5, y, 0, 0, 1); y += 6;
    drawstr("model aircraft and RC hobby FPV OSDs,", 5, y, 0, 0, 1); y += 6;
    drawstr("which are usually too limited, way too ", 5, y, 0, 0, 1); y += 6;
    drawstr("expensive, or closed source.", 5, y, 0, 0, 1); y += 12;
    
    drawstr("The next few demos show just some of the ", 5, y, 0, 0, 1); y += 6;
    drawstr("features of Super OSD. Enjoy...", 5, y, 0, 0, 1); y += 6;
}

void demo_vertical_lines()
{
	int i;
	BDRAW = 0;
	BDISP = 0;
	// Draw some lines.
	for(i = 0; i < 256; i += 5)
	{
		dvline(i, 0, 191, 2);
	}
}

void demo_horizontal_lines()
{
	int i;
	BDRAW = 0;
	BDISP = 0;
	// Draw some lines.
	for(i = 0; i < 191; i += 5)
	{
		dhline(0, 255, i, 2);
	}
}

void demo_aligned_text()
{
	int y = 5, xx, yy;
	char buff[2];
	
	draw_text_aligned("-- Text Demos --",  OSD_WIDTH / 2, OSD_HEIGHT - 15, HALIGN_CENTER, VALIGN_BOTTOM, 1, 0, 0);
	draw_text_aligned("Text can be aligned in any way", 5, y, HALIGN_LEFT, VALIGN_MIDDLE, 1, 0, 0); y += 12;
	draw_text_aligned("Left aligned",  5, y, HALIGN_LEFT, VALIGN_MIDDLE, 1, 0, 0); y += 6;
	draw_text_aligned("Center aligned",  OSD_WIDTH / 2, y, HALIGN_CENTER, VALIGN_MIDDLE, 1, 0, 0); y += 6;
	draw_text_aligned("Right aligned",  OSD_WIDTH, y, HALIGN_RIGHT, VALIGN_MIDDLE, 1, 0, 0); y += 12;
	draw_text_aligned("Many visible ASCII chars implemented", OSD_WIDTH / 2, y, HALIGN_CENTER, VALIGN_MIDDLE, 1, 0, 0); y += 6;
	
	dfrect(0, y, OSD_WIDTH, 120, 1); y += 6;
	
	for(yy = 0; yy < 16; yy++)
	{
		for(xx = 0; xx < 16; xx++)
		{
			buff[0] = xx + (yy * 16);
			buff[1] = '\0';
			draw_text_aligned(buff, 15 + (xx * 15), y + (yy * 7), HALIGN_CENTER, VALIGN_MIDDLE, 1, 0, 1);
		}
	}
}

int demo()
{
	int i, k;
	
	while(1)
	{
		BDISP = 0;
		BDRAW = 1;
	
		for(i = 0; i < 100; i++)
		{
			demo_intro_text2();
			BDISP = 1 - BDISP;
			BDRAW = 1 - BDRAW;
		}
		for(i = 0; i < 100; i++)
		{
			fill_mem(0x0000);
			demo_aligned_text();
			BDISP = 1 - BDISP;
			BDRAW = 1 - BDRAW;
		}
		for(i = 0; i < 10; i++)
		{
			demo_vertical_lines();
			delay(100);
			demo_horizontal_lines();
			delay(100);
		}
		//PORTB ^= 1 << FPSPIN;
	}
	
	return 1;
}

