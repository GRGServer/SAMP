// Bank configuration
#define BANK_PIN_MIN					1000
#define BANK_PIN_MAX					9999
#define BANK_PIN_MAXATTEMPTS				5


// Money/Cash transaction types
#define CASHTRANS_PAYDAY				"PAYDAY"
#define CASHTRANS_POWERTAX				"POWERTAX"
#define CASHTRANS_VEHICLETAX				"VEHICLETAX"


// Chat configuration
#define CHAT_MAXDISTANCE				100


// Colors
#define COLOR_BAR_CRITICAL				0x600000FF
#define COLOR_BAR_OK					0x006000FF
#define COLOR_BAR_WARNING				0x606000FF
#define COLOR_CHAT_ADMINS				0x9EAFA0FF
#define COLOR_CHAT_ALL					0xAAFFAAFF
#define COLOR_CHAT_INRANGE				0xFFFFFFFF
#define COLOR_CHAT_JOB					0xAAAAFFFF
#define COLOR_CHAT_PLAYER				0xFFFA00FF
#define COLOR_ERROR					0xFF0000FF
#define COLOR_INFO					0xFF8C55FF
#define COLOR_JOINLEAVE					0x74E800FF
#define COLOR_MARKER_OBJECT				0x00FF00FF
#define COLOR_ME					0x00FF40FF
#define COLOR_NPCCOMMAND				0x000000FF
#define COLOR_SYSTEM					0xC0C0C0FF
#define COLOR_TEXTLABEL					0xFF8C55FF
#define COLOR_USAGE					0x008000FF
#define COLOR_WARNING					0xFF6000FF


// Files
#define FILE_COMMANDS					"commands.txt"
#define FILE_LANGUAGESTRINGS				"scriptfiles/languagestrings.dat"
#define FILE_LASTCHANGES				"svn_changes"
#define FILE_OBJECTMODELS				"objectmodels.dat"
#define FILE_RUNNINGREVISION				"running_revision"
#define FILE_SAVEINFO					"saved_info.txt"
#define FILE_STABLEREVISION				"stable_revision"
#define FILE_UPDATENOTIFICATION				"update_log"
#define FILE_WEAPONS					"weapons.dat"
#define FILE_ZONES					"zones.dat"


// FlyCam configuration
#define FLYCAM_SPEED_FAST				40
#define FLYCAM_SPEED_NORMAL				10
#define FLYCAM_SPEED_SLOW				3


// Gas station configuration
#define GASSTATION_MAXDIFFERENCE			10// Maximum difference between minimum and maximum gas price
#define GASSTATION_MINPRICE				167// Minimum gas price
#define GASSTATION_REFUELSPEED				500// Time per liter


// Hotel configuration
#define HOTEL_RECEPTION_ANGLE				273.733
#define HOTEL_RECEPTION_INTERIOR			15
#define HOTEL_RECEPTION_POSX				2217.28
#define HOTEL_RECEPTION_POSY				-1150.53
#define HOTEL_RECEPTION_POSZ				1025.8
#define HOTEL_ROOM_INTERIOR				70


// Jobs
#define JOB_ADAC					2
#define JOB_ARMEE					8
#define JOB_PARAMEDIC					6
#define JOB_BANK					7
#define JOB_BUSDRIVER					12
#define JOB_ESTATEAGENTS				3
#define JOB_GOVERMENT					11
#define JOB_POLICE					5
#define JOB_MOBILESELLER				13
#define JOB_SCHOOLDRIVER				9
#define JOB_TAXI					10
#define JOB_TRUCKER					4
#define JOB_UNEMPLOYED					0
#define JOB_VEHICLEDEALER				1


// Light objects
#define LIGHTOBJECT_MAXCOLORS				2


// Limits
#define MAX_DISTANCECALCELEMENTS			4096
#define MAX_DYNAMIC_OBJECTS				2000
#define MAX_FUNCTION_NAME				32
#define MAX_GPS_NODES					500
#define MAX_MONEY					100000.00
#define MAX_NAVITARGETS					10// Number of selectable navi targets
#define MAX_NPC_MULTIRECS				10// Number of recordings asigned to a MultiRec NPC
#define MAX_OBJECTMODELID				20000// Highest object model ID = Size of objectModels array because the array index is the modelID
#define MAX_SPEEDCAMERAS				100// Maximum number of speed cameras


// Player needs
#define NEEDS_BLADDER					0.05
#define NEEDS_ENERGY					0.01
#define NEEDS_HUNGER					0.02
#define NEEDS_THIRST					0.03

#define NEEDS_CRITICAL					30
#define NEEDS_WARNING					50


// News configuration
#define NEWS_LINELENGTH					100// Maximum length of a news line
#define NEWS_MAXIMUM					10// Maximum number of news items to show


// NPC configuration
#define NPC_SCRIPTNAME					"recording"


// Pay Day configuration
#define PAYDAY_INTERVAL					3600// 1 hour


// Register values
#define REGISTER_PASSWORD_MAX				20// Also used for password changing
#define REGISTER_PASSWORD_MIN				3 // Also used for password changing


// Sounds
#define SOUND_COMMAND_DENIED				5203
#define SOUND_COMMAND_ERROR				1085
#define SOUND_COMMAND_OK				1138
#define SOUND_NAVITARGETREACHED				1057
#define SOUND_OBJECTPLACED				31810
#define SOUND_PICKUPEVENT				1150


// Speed camera configuration
#define SPEEDCAMERA_DISTANCE				40
#define SPEEDCAMERA_OBJECTMODEL				18880
#define SPEEDCAMERA_TOLERANCE				5


// Spawn properties
#define SPAWN_ANGLE					270.0
#define SPAWN_CAMERAPOSX				2037.0778
#define SPAWN_CAMERAPOSY				1349.0790
#define SPAWN_CAMERAPOSZ				13.8203
#define SPAWN_POSX					2032.0778
#define SPAWN_POSY					1344.0790
#define SPAWN_POSZ					10.8203


// Streamer configuration
#define STREAMER_OBJECTDISTANCE				300


// String sizes
#define STRINGLENGTH_CHATMODE				16
#define STRINGLENGTH_CPMISSION				100
#define STRINGLENGTH_DATETIME				20
#define STRINGLENGTH_DIALOGNAME				MAX_FUNCTION_NAME - 4// 4 = "DR_" + 1 (For 0 byte)
#define STRINGLENGTH_JOBNAME				100
#define STRINGLENGTH_LANGUAGE				3
#define STRINGLENGTH_LANGUAGESTRING			256
#define STRINGLENGTH_LANGUAGESTRINGNAME			100
#define STRINGLENGTH_LOCATION				100
#define STRINGLENGTH_NUMBERPLATE			8
#define STRINGLENGTH_OBJECTFILENAME			50
#define STRINGLENGTH_OBJECTMODELNAME			21
#define STRINGLENGTH_PICKUPTYPE				20
#define STRINGLENGTH_PROPERTYTYPE			10
#define STRINGLENGTH_RADIOSTATIONNAME			30
#define STRINGLENGTH_URL				100
#define STRINGLENGTH_VEHICLECOLORS			100
#define STRINGLENGTH_VEHICLENAME			20
#define STRINGLENGTH_VEHICLETYPE			16
#define STRINGLENGTH_WEAPONNAME				20
#define STRINGLENGTH_ZONENAME				30


// 3D text labels
#define TEXTLABEL_DRAWDISTANCE				20


// Timers
#define TIMER_EVERYMINUTE				60000// 1 minute
#define TIMER_FAST					250// 1/4 seconds
#define TIMER_FLYCAM					10// Ultra fast to have a smooth fly cam (Only runs while fly cam is enabled)
#define TIMER_HIDERADIODISPLAY				3000// Hide radio display after 3 seconds
#define TIMER_PEE					1000// Interval of pee update (Only runs while a player is pissing)
#define TIMER_PICKUPTIMEOUT				2000// Only show pickup message if the player didn't pick up a pickup before the timeout of 2 seconds has been reached
#define TIMER_SLOW					5000// 5 seconds
#define TIMER_STABLECHECK				600000// Mark server as stable after 10 minutes
#define TIMER_SCREENFADER				10// Ultra fast to have a smooth screen fader (Only runs while fading)

// Vehicle configuration
#define VEHICLE_MINHEALTH				30


// Virtual Worlds (starting IDs)
#define VIRTUALWORLD_BANK				1000
#define VIRTUALWORLD_HOUSE				2000