// Money/Cash transaction types
#define CASHTRANS_PAYDAY			"PAYDAY"
#define CASHTRANS_POWERTAX			"POWERTAX"
#define CASHTRANS_VEHICLETAX		"VEHICLETAX"


// Chat configuration
#define CHAT_MAXDISTANCE			100


// Colors
#define COLOR_CHAT_ALL				0xAAFFAAAA
#define COLOR_CHAT_INRANGE			0xFFFFFFAA
#define COLOR_CHAT_JOB				0xAAAAFFAA
#define COLOR_ERROR					0xFF0000AA
#define COLOR_INFO					0xFF8C55FF
#define COLOR_IRC					0x33AA33AA
#define COLOR_JOINLEAVE				0x74E80099
#define COLOR_ME					0x00FF40AA
#define COLOR_NPCCOMMAND			0x00000000
#define COLOR_SYSTEM				0xC0C0C0AA
#define COLOR_TEXTLABEL				0xFF8C55FF
#define COLOR_USAGE					0x008000AA


// Files
#define FILE_COMMANDS				"commands.txt"
#define FILE_LANGUAGESTRINGS		"languagestrings.xml"
#define FILE_LASTCHANGES			"svn_changes"
#define FILE_RUNNINGREVISION		"running_revision"
#define FILE_STABLEREVISION			"stable_revision"
#define FILE_UPDATENOTIFICATION		"update_log"


// Gas station configuration
#define GASSTATION_MAXDIFFERENCE	15// Maximum difference between minimum and maximum gas price
#define GASSTATION_MINPRICE			158// Minimum gas price
#define GASSTATION_REFUELSPEED		500// Time per liter


// Hotel configuration
#define HOTEL_RECEPTION_ANGLE		273.733
#define HOTEL_RECEPTION_INTERIOR	15
#define HOTEL_RECEPTION_POSX		2217.28
#define HOTEL_RECEPTION_POSY		-1150.53
#define HOTEL_RECEPTION_POSZ		1025.8
#define HOTEL_ROOM_INTERIOR			70


// IRC credentials
#define IRC_CHANNEL					"#grgserver"
#define IRC_HOST					"127.0.0.1"
#define IRC_PORT					6667
#define IRC_SSL						false
#define IRC_USERNAME				"grgserver"


// Jobs
#define JOB_ADAC					2
#define JOB_ARMEE					8
#define JOB_AMBULANCE				6
#define JOB_BANK					7
#define JOB_ESTATEAGENTS			3
#define JOB_POLICE					5
#define JOB_SCHOOLDRIVER			9
#define JOB_TAXI					10
#define JOB_TRUCKER					4
#define JOB_UNEMPLOYED				0
#define JOB_VEHICLEDEALER			1


// Language configuration
#define LANGUAGE_ENGLISH			0
#define LANGUAGE_GERMAN				1
#define LANGUAGE_MAXSTRINGS			500


// Light objects
#define LIGHTOBJECT_MAXCOLORS		2


// Limits
#define MAX_FUNCTION_NAME			32
#define MAX_MONEY					999999.99// Display on screen


// MySQL database credentials
#define MYSQL_DATABASE				"grg_server"
#define MYSQL_HOST					"127.0.0.1"
#define MYSQL_PASSWORD				"9wLjVfZLJPHbnS5A"
#define MYSQL_USERNAME				"grg_server"


// News configuration
#define NEWS_LINELENGTH				100// Maximum length of a news line
#define NEWS_MAXIMUM				10// Maximum number of news items to show


// NPC configuration
#define NPC_SCRIPTNAME				"npcplayer"


// Pay Day configuration
#define PAYDAY_INTERVAL				3600// 1 hour


// Register values
#define REGISTER_PASSWORD_MAX		20// Also used for password changing
#define REGISTER_PASSWORD_MIN		3 // Also used for password changing
#define REGISTER_SKIN_FEMALE		12
#define REGISTER_SKIN_MALE			15


// Sounds
#define SOUND_COMMAND_DENIED		5203
#define SOUND_COMMAND_ERROR			1085
#define SOUND_COMMAND_OK			1138
#define SOUND_NAVITARGETREACHED		1057
#define SOUND_OBJECTPLACED			31810
#define SOUND_PICKUPKEYPRESSED		1150


// Spawn properties
#define SPAWN_ANGLE					270.0
#define SPAWN_CAMERAPOSX			2037.0778
#define SPAWN_CAMERAPOSY			1349.0790
#define SPAWN_CAMERAPOSZ			13.8203
#define SPAWN_POSX					2032.0778
#define SPAWN_POSY					1344.0790
#define SPAWN_POSZ					10.8203


// String sizes
#define STRINGLENGTH_DATETIME		20
#define STRINGLENGTH_LANGUAGESTRING	256
#define STRINGLENGTH_LOCATION		100
#define STRINGLENGTH_NUMBERPLATE	8
#define STRINGLENGTH_OBJECTNAME		20
#define STRINGLENGTH_PICKUPTYPE		20
#define STRINGLENGTH_PROPERTYTYPE	10
#define STRINGLENGTH_VEHICLENAME	20
#define STRINGLENGTH_VEHICLETYPE	16
#define STRINGLENGTH_WEAPONNAME		20


// 3D text labels
#define TEXTLABEL_DRAWDISTANCE		20


// Timers
#define TIMER_EVERYMINUTE			60000// 1 minute
#define TIMER_FAST					250// 1/4 seconds
#define TIMER_HIDERADIODISPLAY		3000// Hide radio display after 3 seconds
#define TIMER_PICKUPTIMEOUT			2000// Only show pickup message if the player didn't pick up a pickup before the timeout of 2 seconds has been reached
#define TIMER_SLOW					5000// 5 seconds
#define TIMER_STABLECHECK			600000// Mark server as stable after 10 minutes
#define TIMER_SCREENFADER			10// Ultra fast to have a smooth screen fader (Only runs while fading)


// Vehicle configuration
#define VEHICLE_MAXATTACHEDOBJECTS	10
#define VEHICLE_MINHEALTH			30


// Virtual Worlds (starting IDs)
#define VIRTUALWORLD_BANK			1000
#define VIRTUALWORLD_HOUSE			2000