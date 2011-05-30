/**
 * "Value-add" OSD functions that are not part of the core
 * library for simplicities sake or because they are too
 * complex to reliably implement in assembly.
 *
 * These are optional, though some modules depend on them.
 */
 
#define	HALIGN_LEFT		1
#define	HALIGN_CENTER	2
#define	HALIGN_RIGHT	3
#define	VALIGN_TOP		1
#define	VALIGN_MIDDLE	2
#define	VALIGN_BOTTOM	3

#define MIN(x, y) ((y) + (((x) - (y)) & -((x) < (y))));

struct TextBBox
{
	int x, y;
	int width, height;
};

void draw_rect_outline(int x, int y, int width, int height, int mode);
void draw_line(int x0, int y0, int x1, int y1, int mode);
void calc_text_bbox(int x, int y, char *str, int fontnum, int xs, struct TextBBox *bboxptr);
void draw_text_aligned(char *str, int x, int y, int ha, int va, int xs, int fontnum, int mode);
inline void draw_text_bbox(char *str, struct TextBBox bbox, int xs, int fontnum, int mode);
void bbox_text_aligned(char *str, int x, int y, int ha, int va, int xs, int fontnum, struct TextBBox *newbbox);
void draw_text_paragraph(char *str, int x0, int y0, int w, int h, int ha, int fontnum, int xs, int ys);