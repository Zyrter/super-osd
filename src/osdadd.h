/**
 * "Value-add" OSD functions that are not part of the core
 * library for simplicities sake or because they are too
 * complex to reliably implement in assembly.
 *
 * These are optional.
 */
 
#define	HALIGN_LEFT		1
#define	HALIGN_CENTER	2
#define	HALIGN_RIGHT	3
#define	VALIGN_TOP		1
#define	VALIGN_MIDDLE	2
#define	VALIGN_BOTTOM	3

struct TextBBox
{
	int x, y;
	int width, height;
};

void calc_text_bbox(int x, int y, char *str, int fontnum, int xs, struct TextBBox *bboxptr);
void update_fps(); 
void draw_fps();
void draw_text_aligned(char *str, int x, int y, int ha, int va, int xs, int fontnum, int mode);
void draw_text_bbox(char *str, int x0, int y0, int w, int h, int ha, int fontnum, int xs, int ys);