/**
 * Head Up Display core.
 *
 * TODO: modularise, modularise, modularise!!
 */

#include "hudwidgets.h"
#include "hud.h"
#include "osd.h"

void hud_rc_plane_single_frame()
{
	fill_mem(0x0000);
	hud_draw_lin_compass(OSD_WIDTH / 2, 20, 30, 5, 90, 220);
	BDISP = 1 - BDISP;
	BDRAW = 1 - BDRAW;
}