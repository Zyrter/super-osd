/**
 * Super OSD, software revision 3
 * Copyright (C) 2010 Thomas Oldbury
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "gfx.h"
#include "gfx_game_engine.h"
#include "fpexpansion.h"
#include "useful.h"

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

/**
 * Demo struct of waypoints.
 */
struct Point3D_SmLLA track[11];
int current_wp = 0;

/**
 * These files handle the rendering of a virtual world and handle
 * video games / virtual challenges.
 *
 * They depend heavily on floating point calculations, so can be 
 * slow at times. However, where possible, results are cached and
 * optimal routes to calculations are taken.
 *
 * Some may critique me for premature optimisation. This is because
 * I do actually do this, because on a processor with not much
 * processing power, it is necessary.
 *
 * This code may be moved to the PIC24F later.
 */

#include "gfx_game_engine.h"
#include "osd.h"
#include <math.h>

/**
 * calc_bearing: Calculate bearing (in radians) from one lat/lon
 * pair to another.
 *
 * @param	from	lat/lon from pair
 * @param	to		lat/lon to pair
 *
 * @return	bearing in radians
 */
float bearing(struct Point2D_LL from, struct Point2D_LL to)
{
	// Partially based off http://www.movable-type.co.uk/scripts/latlong.html.
	float lat1 = DEG2RAD(from.lat);
	float lat2 = DEG2RAD(to.lat);
	float dlon = DEG2RAD(to.lon - from.lon);
	float cos_lat2 = cos(lat2);
	float y = sin(dlon) * cos_lat2;
	float x = (cos(lat1) * sin(lat2)) - (sin(lat1) * cos_lat2 * cos(dlon));
	return atan2(y, x) + CONST_PI;
}

/**
 * angle_dist_rad: Computes the distance between two angles,
 * handling numerical overflow. Angles are in radians.
 *
 * @param	a1	first angle
 * @param	a2	second angle
 *
 * @return	absolute distance between angles (a1 -> a2) 
 */
float angle_dist_rad(float a1, float a2)
{
	return fmod(a1 + (CONST_PI - a2), CONST_2PI) - CONST_PI;
}

/**
 * angle_dist_deg: Computes the distance between two angles,
 * handling numerical overflow. Angles are in degrees.
 *
 * @param	a1	first angle
 * @param	a2	second angle
 *
 * @return	absolute distance between angles (a1 -> a2)
 */
float angle_dist_deg(float a1, float a2)
{
	float tent_dist = a1 + 180.0f - a2;
	// only call fmod if necessary
	if(tent_dist > 720.0f) tent_dist = fmod(tent_dist, 360.0f);
	else if(tent_dist > 360.0f) tent_dist -= 360.0f;
	return tent_dist - 180.0f;
	//return fmod(a1 + (180.0f - a2), 360.0f) - 180.0f;
}

/**
 * lerp2: Linear interpolation between two variables and 
 * a given fraction.
 *
 * @param	a	first variable
 * @param	b	second variable
 * @param	f	fraction of interpolation: 0.0f = all a, 0.5f = halfway, 1.0f = all b
 */
float lerp2(float a, float b, float f)
{
	// Is there a more efficient way of doing this(?)
	return a + ((b - a) * f);
	//return (a * (1.0f - f)) + (b * f);
}

/**
 * hypot2: pythagorean distance with two variables.
 *
 * @param	a	distance in x
 * @param	b	distance in y
 */
float hypot2(float a, float b)
{
	// sqrt -> sqrtf(?)
	return sqrt((a * a) + (b * b));
}

/**
 * esthypot2: fast pythagorean distance (estimate.) This is approximately 
 * twice as fast (467 cycles vs. 828 cycles.)
 *
 * It is not accurate for distances where one variable is much bigger
 * than the other.
 *
 * This algorithm comes from http://en.wikipedia.org/wiki/Talk:Euclidean_distance.
 * It's good for long distances and is a reasonable approximation using only
 * floating point add, absolute sign, multiply and compare.
 *
 * @param	dx	distance in x
 * @param	dy	distance in y
 */
float esthypot2(float dx, float dy)
{
	float dytemp;
	// optimisations for zero length edges
	//if(dy == 0.0f) return dx;
	//if(dx == 0.0f) return dy;
	dx = fabs(dx);
	dy = fabs(dy);
	if(dy > dx)
	{
		// swap the two variables
		dytemp = dy;
		dy = dx;
		dx = dytemp;
	}
	return (0.41f * dx) + (0.941246f * dy);
}

/**
 * hypot3: pythagorean distance with three variables. Typically 1094 cycles.
 *
 * @param	a	distance in x
 * @param	b	distance in y
 * @param	c	distance in z
 */
float hypot3(float a, float b, float c)
{
	return sqrtf((a * a) + (b * b) + (c * c));
}

// There is no esthypot3 function because hypot3 is faster.

/**
 * rotate2: rotate an x,y about an origin.
 *
 * @param	px		x coordinate to rotate
 * @param	py		y coordinate to rotate
 * @param	ox		x coordinate of origin
 * @param	oy		y coordinate of origin
 * @param	rx		pointer for result x
 * @param	ry		pointer for result y
 * @param	theta	angle to rotate by (radians)
 *
 * FIXME: appears to cause memory corruption(?)
 */
void rotate2(float px, float py, float ox, float oy, float *rx, float *ry, float theta)
{
	float costheta = cosf(theta), sintheta = sinf(theta);
	*rx = (costheta * (px - ox)) - (sintheta * (py - oy)) + ox;
	*ry = (sintheta * (px - ox)) + (costheta * (py - oy)) + oy;
}

/**
 * compute_3d_transform: This function is the base for 
 * many further features. It computes the virtual position
 * of an object as projected on a camera. The result is 
 * passed by reference.
 *
 * @param	p_viewer	the viewer / camera (a WorldCamera struct)
 * @param	p_subj		the subject point (a Point3D_LLA)
 * @param	res			pointer to result structure
 * @param	cliph		clip heurestic: distance at which to not calculate points.
 *
 * If you ever hated trigonometry in school, you better get
 * ready to hate it some more, but it's really cool stuff!
 */
void compute_3d_transform(struct WorldCamera *p_viewer, struct Point3D_LLA *p_subj, struct Point2D_CalcRes *res, float cliph)
{
	// Initialize results struct. (would memset be better here?)
	res->flags = 0;
	res->pos.x = 0;
	res->pos.y = 0;
	res->est_dist = 0;
	res->small_dist = 0;
	res->h_angle = 0;
	res->v_angle = 0;
	// Estimate the distance to the waypoint. This isn't intended to replace
	// proper lat/lon distance algorithms, but provides a general indication
	// of how far away our subject is from the camera. It works accurately for 
	// short distances of less than 1km, but doesn't give distances in any
	// meaningful unit (lat/lon distance?)
	res->small_dist = hypot2(p_viewer->p.lat - p_subj->lat, p_viewer->p.lon - p_subj->lon);
	res->est_dist = res->small_dist * 2000.0f;
	// Save precious cycles if outside of visible world.
	if(res->est_dist > cliph)
		goto quick_exit;
	// Compute the horizontal angle to the point. 
	// atan2(y,x) so atan2(lon,lat) and not atan2(lat,lon)!
	res->h_angle = angle_dist_deg(RAD2DEG(atan2f(p_viewer->p.lon - p_subj->lon, p_viewer->p.lat - p_subj->lat)), p_viewer->yaw);
	//res->small_dist = res->est_dist * 0.0025f; // by trial and error this works well.
	// Using the estimated distance and altitude delta we can calculate
	// the vertical angle.
	res->v_angle = RAD2DEG(atan2f(p_viewer->p.alt - p_subj->alt, res->est_dist));
	// Normalize the results to fit in the field of view of the camera if
	// the point is visible. If they are outside of (0,hfov] or (0,vfov]
	// then the point is not visible.
	res->h_angle += p_viewer->hfov * 0.5f;
	res->v_angle += p_viewer->vfov * 0.5f;
	// Set flags. Rolling seems to exclude some values - need to work on this!
	if(res->h_angle < 0 || res->h_angle > p_viewer->hfov)
		res->flags |= X_OVER;
	if(res->v_angle < 0 || res->v_angle > p_viewer->vfov)
		res->flags |= Y_OVER;
	if(!(res->flags & X_OVER || res->flags & Y_OVER))
	{
		res->pos.x = (res->h_angle / p_viewer->hfov) * p_viewer->width;
		res->pos.y = (res->v_angle / p_viewer->vfov) * p_viewer->height;
		// If roll is nonzero rotate about the display surface's center.
		if(p_viewer->roll >= 0.5f)
		{
			float theta_rad = DEG2RAD(p_viewer->roll);
			float px = res->pos.x, py = res->pos.y;
			float ox = p_viewer->width / 2, oy = p_viewer->height / 2;
			float costheta = cosf(theta_rad), sintheta = sinf(theta_rad);
			res->pos.x = (costheta * (px - ox)) - (sintheta * (py - oy)) + ox;
			res->pos.y = (sintheta * (px - ox)) + (costheta * (py - oy)) + oy;
			if(res->pos.x < 0 || res->pos.x > p_viewer->width)
				res->flags |= X_OVER;
			if(res->pos.y < 0 || res->pos.y > p_viewer->height)
				res->flags |= Y_OVER;
		}
	}
	return;
quick_exit:
	res->flags |= X_OVER | Y_OVER;
	return;
}

/**
 * demo_game: Demonstrates game engine functions. 
 */
int demo_game()
{
	char buff[100];
	long int last_time = 0;
	int i, r, ctr = 0, fps = 0, vis_wps = 0;
	struct WorldCamera p_viewer;
	struct Point2D_CalcRes p_res;
	struct Point3D_LLA point;
	// Initialize waypoints.
	SET_WP(track, 0, CF2L(51.26), CF2L(-1.08), 100);
	SET_WP(track, 1, CF2L(51.25), CF2L(-1.08), 133);
	SET_WP(track, 2, CF2L(51.24), CF2L(-1.08), 166);
	SET_WP(track, 3, CF2L(51.23), CF2L(-1.08), 200);
	SET_WP(track, 4, CF2L(51.20), CF2L(-1.07), 100);
	SET_WP(track, 5, CF2L(51.15), CF2L(-1.09), 100);
	SET_WP(track, 6, CF2L(51.10), CF2L(-1.07), 100);
	SET_WP(track, 7, CF2L(51.05), CF2L(-1.09), 100);
	SET_WP(track, 8, CF2L(51.00), CF2L(-1.07), 100);
	SET_WP(track, 9, CF2L(50.95), CF2L(-1.08), 100);
	SET_WP(track, 10, CF2L(50.70), CF2L(-1.08), 120);
	// Initialize viewer/camera.
	p_viewer.hfov = 30;
	p_viewer.vfov = 30;
	p_viewer.yaw = 0;
	p_viewer.roll = 0;
	p_viewer.pitch = 0;
	p_viewer.width = 192;
	p_viewer.height = 128;
	p_viewer.p.lat = 51.30f;
	p_viewer.p.lon = -1.08f;
	p_viewer.p.alt = 100.0f;
	while(1)
	{
		fill_buffer(draw_buffer_mask, 0x0000);
		fill_buffer(draw_buffer_level, 0x0000);
		ctr++;
		if(tv_time != last_time)
		{
			fps = ctr;
			ctr = 0;
			last_time = tv_time;
		}
		memset(buff, 0, 20);
		strcat(buff, "FPS:");
		my_itoa(fps, buff + strlen(buff));
		//strcat(buff, "\nWP :");
		//my_itoa(vis_wps, buff + strlen(buff));
		vis_wps = 0;
		write_string(buff, 0, 0, 0, 0, TEXT_VA_TOP, TEXT_HA_LEFT, 0, 1);
		memset(buff, 0, 20);
		strcat(buff, "ROL:");
		my_itoa(p_viewer.roll, buff + strlen(buff));
		write_string(buff, DISP_WIDTH, 0, 0, 1, TEXT_VA_TOP, TEXT_HA_RIGHT, 0, 1);
		memset(buff, 0, 20);
		fpllstring(p_viewer.p.lat, 4, buff + strlen(buff));
		strcat(buff, "N ");
		fpllstring(p_viewer.p.lon, 4, buff + strlen(buff));
		strcat(buff, "E");
		write_string(buff, 0, DISP_HEIGHT, 0, 1, TEXT_VA_BOTTOM, TEXT_HA_LEFT, 0, 1);
		// For each waypoint, compute the transform.
		// For this to work properly, the waypoints list must be sorted by distance.
		for(i = SIZEOF_ARRAY(track) - 1; i > 0; i--)
		{
			point.lat = CL2F(track[i].lat);
			point.lon = CL2F(track[i].lon);
			point.alt = track[i].alt;
			compute_3d_transform(&p_viewer, &point, &p_res, 1500.0f);
			if(!(p_res.flags & X_OVER || p_res.flags & Y_OVER))
			{
				if(p_res.small_dist < 0.5f)
					r = 1.0f / p_res.small_dist;
				else
					r = 0;
				if(r > 6 && r < DISP_WIDTH)
				{
					//write_rectangle_outlined(p_res.pos.x - r, p_res.pos.y - r, r * 2, r * 2, 0, 1);
					write_circle_outlined(p_res.pos.x, p_res.pos.y, r, 0, 0, 0, 1);		
				}
				memset(buff, 0, 5);
				my_itoa(i, buff);
				write_string(buff, p_res.pos.x, p_res.pos.y, 0, 1, TEXT_VA_MIDDLE, TEXT_HA_CENTER, 0, 1);
				vis_wps++;
			}
		}
		swap_buffers();
		// adjust viewpoint.
		p_viewer.p.lat -= 0.0005f;
		if(p_viewer.p.lat < 50.65f) p_viewer.p.lat = 51.40f;
		p_viewer.roll += 0.5f;
		if(p_viewer.roll >= 360.0f)
			p_viewer.roll = 0.0f;
	}
	return 1;
}
