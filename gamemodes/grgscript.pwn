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

// Compile time constants (Updated from build script before compiling)
#tryinclude <grgserver/compiler>// Constants updated before compiling (Compiling time, SVN revision, etc.) -> Only used on srv2
#if !defined COMPILER_DATE
	#define COMPILER_DATE "UNDEFINED"
#endif
#if !defined COMPILER_TIME
	#define COMPILER_TIME ""
#endif
#if !defined COMPILER_SVN_REVISION
	#define COMPILER_SVN_REVISION -1
#endif

// GRG Server includes
#include <grgserver/constants>// Constants like colors, dialog IDs, command returns, etc.
#include <grgserver/config>// Configuration data like IRC and MySQL credentials
#include <grgserver/structures>// Structures for arrays like vehicles
#include <grgserver/globals>// Globally used variables like ircBot (Variables which are shared between multiple functions)
#include <grgserver/macros>// Macros like GetStringArg
#include <grgserver/basicfunctions> // Ported functions like str_replace
#include <grgserver/functions>// Stock functions like LoadPlayer
#include <grgserver/gamemode>// Callbacks OnGameModeInit and OnGameModeExit
#include <grgserver/irc>// Callbacks for IRC like IRC_OnConnect
#include <grgserver/players/connect_disconnect>// Callbacks OnPlayerConnect and OnPlayerDisconnect
#include <grgserver/players/dialogs>// Callback OnDialogResponse
#include <grgserver/players/general>// General player callbacks
#include <grgserver/players/pickups>// Callback OnPlayerPickupPickUp
#include <grgserver/players/vehicles>// Player related vehicle callbacks like OnPlayerEnterVehicle
#include <grgserver/timers>// Timers to update various stuff like world time
#include <grgserver/commands/admins>// Admin commands like /addpickup
#include <grgserver/commands/npcs>// NPC commands like /npccmd
#include <grgserver/commands/players>// Player commands like /radio

main()
{
	// Log printing work around (Must be printed with *one* print() command to prevent time from displaying)
	new string[256];
	format(string, sizeof(string), "\n\n*** GRG Server Game Mode ***\n");
	format(string, sizeof(string), "%s\nSVN Revision %d\n", string, COMPILER_SVN_REVISION);
	format(string, sizeof(string), "%sCompile date: %s %s\n", string, COMPILER_DATE, COMPILER_TIME);
	format(string, sizeof(string), "%s\nCopyright 2012 GRG Server\n", string);
	print(string);
}