#include <grgserver\compilerconstantscheck>// Check for constants defined on srv2 and replace with dummy if not existing
#include <grgserver\constants>// Constants like colors, dialog IDs, command returns, etc.
#include <grgserver\config>// Configuration data like IRC and MySQL credentials
#include <grgserver\structures>// Structures for arrays like vehicles
#include <grgserver\globals>// Globally used variables like ircBot (Variables which are shared between multiple functions)
#include <grgserver\macros>// Macros like GetStringArg
#include <grgserver\basicfunctions> // Ported functions like str_replace

// Functions
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


#include <grgserver\gamemode>// Callbacks OnGameModeInit and OnGameModeExit
#include <grgserver\ircchannel>// Callbacks for IRC like IRC_OnConnect
#include <grgserver\connect_disconnect>// Callbacks OnPlayerConnect and OnPlayerDisconnect
#include <grgserver\dialogs>// Callback OnDialogResponse
#include <grgserver\playersgeneral>// General player callbacks
#include <grgserver\pickups>// Callback OnPlayerPickupPickUp
#include <grgserver\vehicles>// Player related vehicle callbacks like OnPlayerEnterVehicle
#include <grgserver\timers>// Timers to update various stuff like world time
#include <grgserver\admincommands>// Admin commands like /addpickup
#include <grgserver\npccommands>// NPC commands like /npccmd
#include <grgserver\playercommands>// Player commands like /radio
#include <grgserver\rconcommands>// RCON commands like reloadpermissions