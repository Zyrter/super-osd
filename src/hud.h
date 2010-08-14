/**
 * Head Up Display core.
 *
 * TODO: modularise, modularise, modularise!!
 */

/**
 * Warnings queue.
 */
struct QueuedWarn
{
	int uid;
	char warnmsg[20];
};

/**
 * RC plane HUD. For testing only!
 */ 
void hud_rc_plane_single_frame();