/**
 * Head Up Display core.
 *
 * TODO: modularise, modularise, modularise!!
 */

#include "hudwidgets.h"
#include "hud.h"
#include "osd.h"
#include "osdadd.h"

int heading = 0;
int airspeed = 0;
int altitude = 0;
int temperature = 0;
int frame_sec = 0;
long int last_seconds = 0;
int fps = 0;
int rssi = 0;
int batt1_voltage = 8350;
long int batt1_current = 10000;
float batt1_mah = 0;
int batt1_mah_max;

struct QueuedWarn warning_messages[8];	// up to 8 warning messages queued.
int warning_queue_pos = 0;
int warning_serve_pos = 0;

unsigned int video_fields_per_sec = 50;
unsigned int half_video_fields_per_sec = 25;
unsigned int quarter_video_fields_per_sec = 12;	// rounded down

/* Work in progress */
void queue_warning(int uid, char *msg)
{
	// Queue a new warning.
	if(warning_queue_pos > (sizeof(warning_messages) - 1))
		return;
	if(strlen(msg) > 19)	// max length 19 chars (20 bytes: 1 nul byte and 19 chars)
		return;
	warning_messages[warning_queue_pos].uid = uid;
	strcpy(warning_messages[warning_queue_pos].warnmsg, msg);
	warning_queue_pos++;
}

void unqueue_warning(int uid)
{
	// Remove a warning from the list. This is done by 
	// setting its UID to -1.
	int i;
	for(i = 0; i < sizeof(warning_messages); i++)
	{
		if(warning_messages[i].uid == uid)
		{
			warning_messages[i].uid = -1;
			return;
		}
	}
}

void get_next_warning(char *buff)
{
	int i;
	// Get the next warning, copy it into buff.
	if(warning_serve_pos > (sizeof(warning_messages) - 1))
		warning_serve_pos = 0;
	do
	{
		strcpy(buff, "hello");
		warning_serve_pos++;
	} while(warning_messages[warning_serve_pos].uid != -1 && i < 8);
}

void hud_init()
{
	queue_warning(1, "Low Battery");
	heading = 0;
	airspeed = 0;
	altitude = 0;
	fps = 0;
	temperature = 25;
	rssi = 1000;
	batt1_current = 10000;
	batt1_voltage = 8350;
	batt1_mah = 0;
	batt1_mah_max = 300;
	// PAL defaults.
	// TODO: Configurable NTSC/PAL modes.
	video_fields_per_sec = 50;
	half_video_fields_per_sec = video_fields_per_sec / 2;
	quarter_video_fields_per_sec = video_fields_per_sec / 4;
}

void hud_rc_plane_single_frame()
{
	// What about NTSC? 
	long int seconds = TIME / video_fields_per_sec;
	long int frame = TIME % video_fields_per_sec;
	int flash = (frame / half_video_fields_per_sec) % 2;
	int flash_fast = (frame / quarter_video_fields_per_sec) % 2;
	if(frame == 0 || 
	   frame == quarter_video_fields_per_sec || 
	   frame == half_video_fields_per_sec || 
	   frame == (quarter_video_fields_per_sec * 3)) // 3 quarters
	{
		// Calculate mAh 4 times per second.
		batt1_mah += batt1_current / 14400.0f;
	}
	// Fill screen.
	fill_mem(0x0000);
	// Update FPS.
	if(seconds != last_seconds)
	{
		fps = frame_sec;
		frame_sec = 0;
		last_seconds = seconds;
	}
	// Draw runtime.
	format_time(seconds, buff);
	draw_text_aligned(buff, 5, 5, HALIGN_LEFT, VALIGN_TOP, 1, 0, 0);
	// Draw FPS.
	my_itoa(fps, buff);
	strcat(buff, " fps");
	draw_text_aligned(buff, 5, 11, HALIGN_LEFT, VALIGN_TOP, 1, 0, 0);
	// Draw outside/air temperature.
	my_itoa(temperature, buff);
	strcat(buff, "^C");	// caret = degrees sign
	draw_text_aligned(buff, 5, 17, HALIGN_LEFT, VALIGN_TOP, 1, 0, 0);
	// Draw RSSI.
	hud_draw_rssi(OSD_WIDTH - 5, 5, HALIGN_RIGHT, VALIGN_TOP, rssi / 10, flash_fast);
	// Draw a battery meter.
	//my_itoa((int)batt1_mah, buff);
	//draw_text_aligned(buff, OSD_WIDTH - 5, 11, HALIGN_RIGHT, VALIGN_TOP, 1, 0, 0);
	hud_draw_battery_meter(OSD_WIDTH - 45, 15, 40, batt1_voltage, batt1_current, batt1_mah, batt1_mah_max);
	// Draw status information.
	if(flash == 1)
	{
		//get_next_warning(buff);
		strcpy(buff, "SIMULATION MODE");
		draw_text_aligned(buff, OSD_WIDTH / 2, OSD_HEIGHT - 50, HALIGN_CENTER, VALIGN_MIDDLE, 1, 0, 0);
		strcpy(buff, "S/W v2.25");
		draw_text_aligned(buff, OSD_WIDTH / 2, OSD_HEIGHT - 44, HALIGN_CENTER, VALIGN_MIDDLE, 1, 0, 0);
	}
	// Draw the meters.
	hud_draw_lin_compass(OSD_WIDTH / 2, 10, 30, 5, 90, heading / 10);
	hud_draw_airspeed_indicator(55, OSD_HEIGHT / 2, 20, 5, 100, airspeed / 10);
	hud_draw_altitude_indicator(OSD_WIDTH - 55, OSD_HEIGHT / 2, 20, 5, 100, altitude / 10);
	// Swap buffers.
	BDISP = 1 - BDISP;
	BDRAW = 1 - BDRAW;
	// Update simulation.
	heading += 2;
	heading %= 3600;
	airspeed += 5;
	altitude += 7;
	rssi -= 1;
	if(rssi < 0) rssi = 1000;
	// Update frame counter.
	frame_sec++;
}