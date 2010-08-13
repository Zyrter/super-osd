/**
 * OSD header.
 *
 * Interfaces to the assembler core.
 */
 
#ifndef	OSD_H
#define	OSD_H

#include <p33fj128gp802.h>

#define	OSD_WIDTH		256
#define	OSD_HEIGHT		192

#define	VERSION_MAJOR	2
#define	VERSION_MINOR	0

#define	HBPIN			15
#define	CTSPIN			14
#define	FPSPIN			13

extern int BDRAW;		// Draw buffer no.
extern int BDISP;		// Display buffer no.

struct TextSize
{
	int width, height;
};

/**
 * Arbiturary delay. As a guide, i = 40 is about 10 fps (100 ms.)
 */
extern void delay(int i);

/**
 * Swap draw & display buffers.
 */
extern void swapbuffs(void);

/**
 * Fill memory with a specific word or clear it. These are very
 * fast because they just write one byte 3,072 times to clear
 * the screen. Over 3,500 screen clears *per second* can be 
 * performed.
 */
extern void fill_mem(unsigned int byte);
extern void clear_mem();

/**
 * Direct pixel manipulation. As each of these routines requires 
 * a lot of cycles (about 50), consider using the other, more 
 * optimised drawing primitives. Only recommended for occasional
 * pixel changes.
 */
extern void setpix(int x0, int y0);
extern void clrpix(int x0, int y0);
extern void togpix(int x0, int y0);
extern void drawpix(int x0, int y0, int mode);

/**
 * Pixel test routine. If a pixel is clear (not set), returns 0 
 * otherwise returns 1.
 */
extern int testpix(int x0, int y0);

/**
 * Write a single character. x,y gives the top left position.
 * Font 0 = 5x5, font 1 = 8x8. More fonts may be implemented later.
 * Page zero must always be selected, or the font will malfunction.
 */
extern void drawchar(char c, int x, int y, int mode, int font);

/**
 * Write a string in page zero or in data space. If the string
 * does not exist in page zero it must be copied to data memory
 * and used from there. x,y gives the top left position and xs
 * gives horizontal spacing.
 */
extern void drawstr(char *str, int x, int y, int mode, int font, int xs);

/**
 * Optimised horizontal line drawing algorithm. This is 100x or 
 * more faster than Bresenham. It writes up to 16 pixels at a 
 * time and uses very clever bit math to handle edge case pixels. 
 */
extern void dhline(int x0, int x1, int y, int mode);

/**
 * Optimised vertical line drawing algorithm. This is very optimised
 * as well. It copies the bit mask that would normally be applied
 * by a setpix routine and repeats it, stepping in the y direction.
 * This yields very fast vertical lines.
 */
extern void dvline(int x, int y0, int y1, int mode);

/**
 * Draw a filled rectangle. This is faster than another method
 * such as drawing individual pixels.
 * 
 * Remember, it takes a width and height, not an x1 and y1! The 
 * width and height can also be negative.
 */
extern void dfrect(int x, int y, int width, int height, int mode);

/**
 * Draw a bitmap type 2. Type 2 is RLE compressed.
 */
extern void drawbm2(const char *imgptr);

/**
 * Return the bounds for a font as a struct TextSize.
 */
extern void textsize(int fontnum, struct TextSize *sz);

#endif	// OSD_H