/**
 * Widgets for the Head Up Display.
 * These include compasses, altimeters, and variometers.
 */

/**
 * Draw a linear compass. The x,y positions give the approximate
 * centre of the compass. The range value gives the range of values
 * which will be displayed. 
 */
void hud_draw_lin_compass(int cx, int cy, int tick_maj, int tick_min, int range, int heading);