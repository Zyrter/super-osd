/**
 * Widgets for the Head Up Display.
 * These include compasses, altimeters, and variometers.
 */

/**
 * Format a time (in seconds) as HH:MM:SS.
 * Buffer must be at least 9 bytes in size.
 */
void format_time(long int time, char *buff);

/**
 * Implementations of itoa and reverse.
 */
void my_itoa(long int n, char s[]);
void my_reverse(char s[]);

/**
 * Draw a linear compass. The x,y positions give the approximate
 * centre of the compass. The range value gives the range of values
 * which will be displayed. 
 */
void hud_draw_lin_compass(int cx, int cy, int tick_maj, int tick_min, int range, int heading);

/**
 * Draw an airspeed indicator. The x,y positions give the approximate
 * centre of the airspeed indicator. The range value gives the range
 * of values which will be displayed.
 */
void hud_draw_airspeed_indicator(int cx, int cy, int tick_maj, int tick_min, int range, int airspeed);

/** 
 * Draw an RSSI indicator.
 */
void hud_draw_rssi(int x, int y, int ha, int va, int rssi, int flash_beat);

/**
 * Draw a battery meter.
 */
void hud_draw_battery_meter(int x, int y, int width, int voltage, long int current, int mah, int max_mah);