/**
 * "Value-add" OSD functions that are not part of the core
 * library for simplicities sake or because they are too
 * complex to reliably implement in assembly.
 *
 * These are optional.
 */

#include "osd.h"
#include "osdadd.h"
#include <stdio.h>

extern long int TIME;		// time, from osd_core.s

char strbuff[64];

int fps = 0;
int framecounter = 0;
long int last_sec = 0;

/**
 * Calculate the bounding box for a string of text.
 *
 * \param		x
 * \param		y
 * \param		string
 * \param		fontnum
 * \param		horizontal spacing
 * \param		pointer to TextBBox struct
 */
void calc_text_bbox(int x, int y, char *str, int fontnum, int xs, struct TextBBox *bboxptr)
{
	// Retrieve font size.
	struct TextSize charsize;
	textsize(fontnum, &charsize);
	// Add xs to width (for horizontal spacing.)
	charsize.width += xs;
	// Multiply by string length to get width.
	int width = charsize.width * strlen(str);
	// Store bbox coords.
	bboxptr->x = x;
	bboxptr->y = y;
	bboxptr->width = width;
	bboxptr->height = charsize.height;
	// Done.
	return;
}

/**
 * Calculate the current FPS of the video and update it
 * if necesary. This should be called at least once per
 * second in the draw loop. When called, it examines the
 * video time stamp and its internal counter to determine
 * the frame rate. The frame rate is the number of times
 * per second this function is called. Note that because
 * frame rate is derived from the video input signal,
 * it depends on the accuracy of that signal.
 */ 
void update_fps()
{
	if(last_sec != TIME)
	{
		// TODO: should some averaging be implemented here?
		fps = framecounter;
		framecounter = 0;
		last_sec = TIME;
	}
	framecounter++;
}

/**
 * Draw the current fps to the screen. This should be 
 * called in turn with update_fps. FPS is drawn in top
 * left (5,5) corner of screen.
 */ 
void draw_fps()
{
	sprintf(strbuff, "%d FPS", fps);
	drawstr(strbuff, 5, 5, 0, 0, 1);
}

/**
 * Draw text with a specified horizontal and vertical 
 * alignment. The alignment determines where the text's
 * (x,y) coordinates fit on the text.
 *
 * \param		string pointer
 * \param		x position
 * \param		y position
 * \param		h alignment (HALIGN_LEFT, HALIGN_CENTER, HALIGN_RIGHT)
 * \param		v alignment (VALIGN_TOP, VALIGN_MIDDLE, VALIGN_BOTTOM)
 * \param		horizontal spacing
 * \param		font number
 * \param		mode (0 = clear, 1 = set or 2 = toggle)
 */
void draw_text_aligned(char *str, int x, int y, int ha, int va, int xs, int fontnum, int mode)
{
	// Calculate the bbox for the string.
	struct TextBBox bbox;
	calc_text_bbox(0, 0, str, fontnum, xs, &bbox);
	// Calculate the x and y topleft coords to blit at.
	int xcalc, ycalc;
	switch(ha)
	{
		case HALIGN_LEFT:
			xcalc = x;
			break;
		case HALIGN_CENTER:
			xcalc = x - (bbox.width / 2) + 1;
			break;
		case HALIGN_RIGHT:
			xcalc = x - bbox.width;
			break;
	}
	switch(va)
	{
		case VALIGN_TOP:
			ycalc = y;
			break;
		case VALIGN_MIDDLE:
			ycalc = y - (bbox.height / 2) + 1;
			break;
		case VALIGN_BOTTOM:
			ycalc = y - bbox.height;
			break;
	}
	// Draw the string.
	drawstr(str, xcalc, ycalc, mode, fontnum, xs);
	return;
}

/**
 * Draw a paragraph of text fitting a bounding box. 
 * This routine is primarily intended for help boxes
 * providing scrollable text. The text can be left
 * aligned for now; future versions may add support
 * for center, right and justified alignment.
 *
 * When dealing with an application with a scrollable
 * text box, it is important to clip the lines 
 * appropriately; this function does not handle that.
 *
 * \param		string pointer
 * \param		top left x position
 * \param		top left y position
 * \param		width
 * \param		height
 * \param		alignment (HALIGN_LEFT only supported)
 * \param		font number
 * \param		x spacing
 * \param		y spacing
 */
void draw_text_bbox(char *str, int x0, int y0, int w, int h, int ha, int fontnum, int xs, int ys)
{
	// TODO
}