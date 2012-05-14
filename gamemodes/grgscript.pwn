#pragma dynamic 8192

// SAMP standard includes
#include <a_samp>

// Custom includes configuration
#define TIMER_FIX_PERFORMANCE_CHECKS false

// Custom includes
#include <formatnumber>
#include <geoip>
#include <irc>
#include <MD5>
#include <mysql>
#include <regex>
#include <sscanf>
#include <streamer>
//#include <timerfix>
#include <xml>
#include <zcmd>

// GRG Server main include
#if defined COMPILE_SERVER
	#include <grgserver\main_server>
#else
	#include <grgserver\main>
#endif

main()
{
	#if defined COMPILE_SERVER
		print("Compiled on server");
	#else
		print("Compiled local");
	#endif
}


/*
Saved stuff:

Cam movement 2: Show jobs "Bus driver" and "Fire fighter"
Cam movement 3: Show gas station

Before cam movement 3: Wait 1500ms

Do cam movement 2: InterpolateCameraPos(1989.23, 101.386, 27.5391, -2009.43, 98.7881, 27.5314, 3000, CAMERA_CUT) + InterpolateCameraLookAt(-1979.84, 92.3615, 27.6875, -2016.57, 92.5771, 27.6875, 3000, CAMERA_CUT)
Do cam movement 3: InterpolateCameraPos(1005.55, -948.811, 42.1938, 1000.18, -943.231, 41.9206, 3500, CAMERA_CUT) + InterpolateCameraLookAt(1011.05, -949.199, 45.9137, 1005.92, -937.631, 42.1797, 3500, CAMERA_CUT)

After cam movement 3: Wait 1500ms -> StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_GASSTATION_BLACK);
*/