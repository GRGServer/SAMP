// SAMP standard includes
#include <a_samp>

// Custom includes
#include <irc>
#include <MD5>
#include <mysql>
#include <sscanf>
#include <zcmd>

// GRG Server includes
#include <grgserver/constants>// Constants like colors, dialog IDs, command returns, etc.
#include <grgserver/config>// Configuration data like IRC and MySQL credentials
#include <grgserver/globals>// Globally used variables like ircBot (Variables which are shared between multiple functions)
#include <grgserver/functions>// Stock functions
#include <grgserver/publics_gamemode>// Publics like OnGameModeInit or OnGameModeExit
#include <grgserver/publics_irc>// IRC publics like IRC_OnConnect
#include <grgserver/publics_players>// Player publics like OnPlayerText
#include <grgserver/commands>// Player commands like /about

main()
{
	print("\n----------------------------------");
	print("GRG Server");
	print("----------------------------------\n");
}