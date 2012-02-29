#include <grgserver\compilerconstantscheck>// Check for constants defined on srv2 and replace with dummy if not existing
#include <grgserver\constants>// Constants like colors, dialog IDs, command returns, etc.
#include <grgserver\config>// Configuration data like IRC and MySQL credentials
#include <grgserver\structures>// Structures for arrays like vehicles
#include <grgserver\globals>// Globally used variables like ircBot (Variables which are shared between multiple functions)
#include <grgserver\macros>// Macros like GetStringArg
#include <grgserver\timers>// Timers to update various stuff like world time

// Functions
#include <grgserver\functions_basic>// Basic C-like functions like str_replace
#include <grgserver\functions_dialogs>// Dialog functions like ShowDialog
#include <grgserver\functions_general>// General functions like CmdUsageMsg
#include <grgserver\functions_mysql>// MySQL functions like GetMySQLValue
#include <grgserver\functions_npcs>// NPC related functions like SendNPCCommand
#include <grgserver\functions_permissions>// Permissions functions like GetPermissionByName
#include <grgserver\functions_pickups>// Pickup functions like AddPickup
#include <grgserver\functions_players_account>// Player account functions like LoadPlayer
#include <grgserver\functions_players_general>// General player functions like GetPlayerNameEx
#include <grgserver\functions_players_teleport>// Teleport player functions like TeleportToInterior
#include <grgserver\functions_vehicles>// Vehicle functions like SaveVehicle

// Callbacks
#include <grgserver\callbacks_dialogs>// Dialog callbacks like OnDialogResponse
#include <grgserver\callbacks_gamemode_init>// Callbacks OnGameModeInit and OnGameModeExit
#include <grgserver\callbacks_irc>// IRC callbacks like like IRC_OnConnect
// #include <grgserver\callbacks_pickups>// Pickup callback OnPlayerPickupPickUp
#include <grgserver\callbacks_players_connect>// Callbacks OnPlayerConnect and OnPlayerDisconnect
#include <grgserver\callbacks_players_general>// General player callbacks like OnPlayerRequestClass
#include <grgserver\callbacks_players_keys>// Callback OnPlayerKeyStateChange
#include <grgserver\callbacks_players_vehicles>// Player related vehicle callbacks like OnPlayerEnterVehicle

// Commands
#include <grgserver\commands_admin>// Admin commands like /money
#include <grgserver\commands_mapper>// Mapper commands like /addpickup
#include <grgserver\commands_moderator>// Moderator commands like /kick
#include <grgserver\commands_npcadmin>// NPC admin commands like /controlnpc
#include <grgserver\commands_npcs>// NPC only commands like /npccmd
#include <grgserver\commands_player>// Player commands like /radio
#include <grgserver\commands_rcon>// RCON commands like reloadpermissions
#include <grgserver\commands_serveradmin>// Server admin commands like /gmx
#include <grgserver\commands_teleport>// Teleport commands like /goto