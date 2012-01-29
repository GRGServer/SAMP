// SAMP standard includes
#include <a_samp>

// Custom includes
#include <irc>
#include <MD5>
#include <mysql>
#include <sscanf>
#include <YSF>
#include <zcmd>

// Get argument as string
#define GetStringArg(%0,%1); \
    for(new i_%0 = 0; ; ++i_%0) \
    { \
        if((%1[i_%0] = getarg((%0), i_%0)) != EOS) \
            continue; \
        else \
            break; \
    }

// GRG Server includes
#include <grgserver/constants>// Constants like colors, dialog IDs, command returns, etc.
#include <grgserver/svn>// SVN specific constants like the current revision
#include <grgserver/config>// Configuration #data like IRC and MySQL credentials
#include <grgserver/globals>// Globally used variables like ircBot (Variables which are shared between multiple functions)
#include <grgserver/functions>// Stock functions
//#include <grgserver/publics_gamemode>// Publics like OnGameModeInit or OnGameModeExit
#include <grgserver/publics_filterscript>// Publics like OnFilterScriptInit or OnFilterScriptExit
#include <grgserver/publics_irc>// IRC publics like IRC_OnConnect
#include <grgserver/publics_players>// Player publics like OnPlayerText
#include <grgserver/commands>// Player commands like /about
