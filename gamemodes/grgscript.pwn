#pragma dynamic 5120

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
#include <timerfix>
#include <xml>
#include <zcmd>

// GRG Server main include
#if defined COMPILE_SERVER
	#include <grgserver/main_server>
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