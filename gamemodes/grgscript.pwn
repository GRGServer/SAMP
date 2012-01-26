// SAMP standard includes
#include <a_samp>

// Custom includes
#include <irc>
#include <MD5>
#include <mysql>
#include <zcmd>

// GRG includes
#include <grg/constants>// Constants like colors, dialog IDs, command returns, etc.
#include <grg/config>// Configuration data like IRC and MySQL credentials
#include <grg/globals>// Globally used variables like ircBot (Variables which are shared between multiple functions)
#include <grg/functions>// Stock functions
#include <grg/publics_gamemode>// Publics like OnGameModeInit or OnGameModeExit
#include <grg/publics_irc>// IRC publics like IRC_OnConnect
#include <grg/publics_players>// Player publics like OnPlayerText
#include <grg/commands>// Player commands like /about

main()
{
	print("\n----------------------------------");
	print("GRG Server");
	print("----------------------------------\n");
}