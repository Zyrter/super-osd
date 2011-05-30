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

#ifndef GFX_GAME_ENGINE_H
#define GFX_GAME_ENGINE_H

#if 0

// Macros for storing and retrieving long coordinates.
#define CF2L(x) ((long int)((x) * 1000000))
#define CL2F(x) ((x) / 1000000.0f)

// Macros to set/retrieve waypoints.
#define SET_WP(wplist, id, latInp, lonInp, altInp) \
	wplist[id].lat = latInp; \
	wplist[id].lon = lonInp; \
	wplist[id].alt = altInp; 

// Flag macros.
#define X_OVER	1
#define Y_OVER	2

// Various data structures & types.
typedef struct Point2D_Pixel { unsigned int x, y; };
typedef struct Point2D_LL { float lat, lon; };
typedef struct Point3D_LLA { float lat, lon, alt; };
// Smaller/faster latitude, longitude and altitude data store.
typedef struct Point3D_SmLLA { long int lat, lon; int alt; };
// Waypoint structure.
typedef struct Waypoint3D 
{ 
	int seq; 
	char shortname[8]; 
	struct Point3D_SmLLA p; 
};
// Camera (i.e. the viewer.) 
typedef struct WorldCamera
{
	// The position of the camera itself.
	struct Point3D_LLA p;
	// Not all of these variables are taken into account yet.
	// At least `yaw` is supported. Basic roll support, but still
	// has some bugs. Pitch is not supported at all. All are in 
	// radians.
	float roll, pitch, yaw;
	// `hfov` and `vfov` could be adjusted to compensate for 
	// different cameras or lenses. In radians.
	float hfov, vfov;
	// Display surface width and height.
	unsigned int width, height;
};
// Structure for storing calculated results (from camera transforms.)
typedef struct Point2D_CalcRes
{
	struct Point2D_Pixel pos;
	float h_angle, v_angle, est_dist, small_dist;
	int flags;
};

// Function prototypes.
float bearing(struct Point2D_LL from, struct Point2D_LL to);
float angle_dist_rad(float a1, float a2);
float angle_dist_deg(float a1, float a2);
float lerp2(float a, float b, float f);
float hypot2(float a, float b);
float esthypot2(float dx, float dy);
float hypot3(float a, float b, float c);
void compute_3d_transform(struct WorldCamera *p_viewer, struct Point3D_LLA *p_subj, struct Point2D_CalcRes *res, float cliph);
int demo_game();

#endif // #if 0

#endif 