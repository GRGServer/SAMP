#include <grgserver\compilerconstantscheck>// Check for constants defined on srv2 and replace with dummy if not existing
#include <grgserver\constants>// Constants like colors, dialog IDs, command returns, etc.
#include <grgserver\config>// Configuration data like IRC and MySQL credentials
#include <grgserver\structures>// Structures for arrays like vehicles
#include <grgserver\globals>// Globally used variables like ircBot (Variables which are shared between multiple functions)
#include <grgserver\macros>// Macros like GetStringArg
#include <grgserver\basicfunctions> // Ported functions like str_replace
#include <grgserver\functions>// Stock functions like LoadPlayer
#include <grgserver\gamemode>// Callbacks OnGameModeInit and OnGameModeExit
#include <grgserver\ircchannel>// Callbacks for IRC like IRC_OnConnect
#include <grgserver\players\connect_disconnect>// Callbacks OnPlayerConnect and OnPlayerDisconnect
#include <grgserver\players\dialogs>// Callback OnDialogResponse
#include <grgserver\players\general>// General player callbacks
#include <grgserver\players\pickups>// Callback OnPlayerPickupPickUp
#include <grgserver\players\vehicles>// Player related vehicle callbacks like OnPlayerEnterVehicle
#include <grgserver\timers>// Timers to update various stuff like world time
#include <grgserver\commands\admins>// Admin commands like /addpickup
#include <grgserver\commands\npcs>// NPC commands like /npccmd
#include <grgserver\commands\players>// Player commands like /radio