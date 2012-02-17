// Admin levels
#define ADMINLEVEL_SERVERADMIN		1338


// Colors
#define COLOR_ERROR					0xA00000AA
#define COLOR_ME					0x00FF40AA
//#define COLOR_PM					0x804000AA
#define COLOR_SYSTEM				0xC0C0C0AA
#define COLOR_CHAT					0xFFFFFFAA
#define COLOR_CHATOWN				0xAAAAAAAA
#define COLOR_IRC					0x33AA33AA
#define COLOR_INFO					0xFF8C55FF
#define COLOR_USAGE					0x008000AA
#define COLOR_JOINLEAVE				0x74E80099
#define COLOR_NPCCOMMAND			0x00000000


// Gas station configuration
#define GASSTATION_REFUELSPEED		500// Time per liter


// Help configuration
#define HELP_COMMANDSPERLINE		5


// IRC credentials
#define IRC_HOST					"127.0.0.1"
#define IRC_PORT					6667
#define IRC_SSL						false
#define IRC_USERNAME				"grgserver"
#define IRC_CHANNEL					"#grgserver"


// MySQL credentials
#define MYSQL_HOST					"srv1.selfcoders.com"
#define MYSQL_USERNAME				"grgserver"
#define MYSQL_PASSWORD				"2RuvHtYb7KRh6PVt"
#define MYSQL_DATABASE				"grgserver"


// Pickups
#define PICKUP_BANK					1559
#define PICKUP_GASSTATION			1008
#define PICKUP_HOUSEAVAILABLE		1273
#define PICKUP_HOUSEBOUGHT			1272


// Register values
#define REGISTER_MINPASSWORD		3
#define REGISTER_MAXPASSWORD		20
#define REGISTER_LEVEL				1
#define REGISTER_ADMINLEVEL			0


// Spawn properties
#define SPAWN_POSX					2032.0778
#define SPAWN_POSY					1344.0790
#define SPAWN_POSZ					10.8203
#define SPAWN_ANGLE					270.0
#define SPAWN_CAMERAPOSX			SPAWN_POSX + 5
#define SPAWN_CAMERAPOSY			SPAWN_POSY + 5
#define SPAWN_CAMERAPOSZ			SPAWN_POSZ + 3


// Timers
#define TIMER_EVERYMINUTE			60000// 1 minute
#define TIMER_FAST					250// 1/4 seconds (Update fuel usage calculation on change!)
#define TIMER_HOURLY				3600000// 1 hour
#define TIMER_SLOW					5000// 5 seconds
#define TIMER_STABLECHECK			600// Mark server as stable after 10 minutes (Not repeating!)


// Vehicle configuration
#define VEHICLE_MINHEALTH			30


// Virtual Worlds (starting IDs)
#define VIRTUALWORLD_BANK			1000
#define VIRTUALWORLD_HOUSE			2000