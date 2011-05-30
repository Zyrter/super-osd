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
char strbuff[64];			// TODO: refactor code to use buff[50]

/**
 * Draw a rectangle with outline. Fast; uses dhline and dvline.
 *
 * \param		x
 * \param		y
 * \param		width
 * \param		height
 * \param		mode
 */
void draw_rect_outline(int x, int y, int width, int height, int mode)
{
	dhline(x, x + width, y, mode);
	dvline(x + width, y, y + height, mode);
	dhline(x + width, x, y + height, mode);
	dvline(x, y + height, y, mode);
}

/**
 * Bresenham's line drawing algorithm.
 *
 * \param		x0
 * \param		y0
 * \param		x1
 * \param		y1
 * \param		mode
 */
void draw_line(int x0, int y0, int x1, int y1, int mode)
{
	// If the line is steep, we need to swap some vars.
	char steep = abs(y1 - y0) > abs(x1 - x0);
	if(steep)
	{
		SWAP_TEMP_INT(x0, y0);
		SWAP_TEMP_INT(x1, y1);
	}
	// If the line is the wrong way round we need to swap some vars.
	if(x0 > x1)
	{
		SWAP_TEMP_INT(x0, x1);
		SWAP_TEMP_INT(y0, y1);
	}
	// Is the line horizontal or vertical? If so, it 
	// makes more sense to draw it with an optimised 
	// line drawing routine.
	if(x0 == x1) 		// vertical
		dvline(x0, y0, y1, mode);
	else if(y0 == y1)	// horizontal
		dhline(x0, x1, y0, mode);
	// Calculate important state variables.
	unsigned int deltax = x1 - x0;
	unsigned int deltay = abs(y1 - y0);
	int error = deltax / 2;
	int ystep;
	if(y0 < y1) ystep = +1;
	else		ystep = -1;
	int x = x0, y = y0;
	int minx = +32767, maxx = -32768;
	for(; x < x1; x++)
	{
		/** FIXME **
		if((deltax - deltay) > 10) // longer in x by 10 more
		{
			// Optimised, hline mode.
			// In this mode, we write long lines of pixels
			// at a time, so nearly horizontal lines are faster.
			if(steep)
			{
				if(y < minx) minx = y;
				if(y > maxx) maxx = y;
			}
			else
			{
				if(y < minx) minx = x;
				if(y > maxx) maxx = x;
			}
		}
		else
		*/
		{
			// Unoptimised.
			if(steep)
			{
				if(mode)
					setpix(y, x);
				else
					clrpix(y, x);
			}
			else
			{
				if(mode)
					setpix(x, y);
				else
					clrpix(x, y);
			}
		}
		error -= deltay;
		if(error < 0)
		{
			//if(minx < +32767 && maxx > -32768)
            //	dhline(minx, maxx, y, mode);
			y += ystep;
			error += deltax;
		}
	}
	if(minx < +32767 && maxx > -32768)
		dhline(minx, maxx, y, mode);
}

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
 * Draw text, given a bbox. (The bbox provides x and y only;
 * width and height are ignored.)
 *
 * \param		string pointer
 * \param		bbox struct
 * \param		horizontal spacing
 * \param		font number
 * \param		mode (0 = clear, 1 = set or 2 = toggle)
 */
inline void draw_text_bbox(char *str, struct TextBBox bbox, int xs, int fontnum, int mode)
{
	drawstr(str, bbox.x, bbox.y, mode, fontnum, xs);
}

/**
 * Draw text with a specified horizontal and vertical alignment. 
 * The alignment determines where the text's (x,y) coordinates 
 * fit on the text; it is not relative to the screen. Invalid
 * alignments assume HALIGN_LEFT and VALIGN_TOP.
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
	struct TextBBox bbox;
	bbox_text_aligned(str, x, y, ha, va, xs, fontnum, &bbox);
	drawstr(str, bbox.x, bbox.y, mode, fontnum, xs);
}

/**
 * Calculate the bounding box for some text with alignment.
 * The alignment determines where the text's (x,y) coordinates 
 * fit on the text; it is not relative to the screen. Invalid
 * alignments assume HALIGN_LEFT and VALIGN_TOP.
 *
 * \param		string pointer
 * \param		x position
 * \param		y position
 * \param		h alignment (HALIGN_LEFT, HALIGN_CENTER, HALIGN_RIGHT)
 * \param		v alignment (VALIGN_TOP, VALIGN_MIDDLE, VALIGN_BOTTOM)
 * \param		horizontal spacing
 * \param		font number
 * \param		bbox pointer; data will be saved here
 */
void bbox_text_aligned(char *str, int x, int y, int ha, int va, int xs, int fontnum, struct TextBBox *newbbox)
{
	// Calculate the bbox for the string.
	struct TextBBox bbox;
	calc_text_bbox(0, 0, str, fontnum, xs, &bbox);
	// Calculate the x and y topleft coords.
	int xcalc, ycalc;
	switch(ha)
	{
		default:
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
		default:
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
	newbbox->x = xcalc;
	newbbox->y = ycalc;
	newbbox->width = bbox.width;
	newbbox->height = bbox.height;
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
void draw_text_paragraph(char *str, int x0, int y0, int w, int h, int ha, int fontnum, int xs, int ys)
{
	// TODO
}

