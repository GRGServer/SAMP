#pragma dynamic 5120

// SAMP standard includes
#include <a_samp>

// Custom includes
#include <formatnumber>
#include <irc>
#include <MD5>
#include <mysql>
#include <regex>
#include <sscanf>
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