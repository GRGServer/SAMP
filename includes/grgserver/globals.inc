// Variables
new attachedObjects[MAX_PLAYERS][VEHICLE_MAXATTACHEDOBJECTS];
new clientMessageString[256];
new gasPriceChangeHour = -1;
new ircBot;
new languageStrings[LANGUAGE_MAXSTRINGS][enum_languageString];
new maxPlayers;
new musicSoundIDs[] = {1062, 1068, 1076, 1097, 1183, 1185, 1187};
new permissions[MAX_PLAYERS][enum_permission];
new pickupLoader[MAX_PICKUPS][enum_pickupLoader];
new pickups[MAX_PICKUPS][enum_pickup];
new playerVariables[MAX_PLAYERS][enum_playerVariable];
new sqlQuery[1024];
new svnRevisionChanged;
new vehicles[MAX_VEHICLES][enum_vehicle];
new vehicleLightObjects[MAX_VEHICLES][enum_neonType][LIGHTOBJECT_MAXCOLORS];
new vehicleModels[212][enum_vehicleModel];
new weapons[][enum_weapon] =
{
	{"Fist", 0},// 0
	{"Brass Knuckles", 1},// 1
	{"Golf Club", 1},// 2
	{"Nightstick", 1},// 3
	{"Knife", 1},// 4
	{"Baseball Bat", 1},// 5
	{"Shovel", 1},// 6
	{"Pool Cue", 1},// 7
	{"Katana", 1},// 8
	{"Chainsaw", 1},// 9
	{"Double-ended Dildo", 1},// 10
	{"Dildo", 1},// 11
	{"Vibrator", 1},// 12
	{"Silver Vibrator", 1},// 13
	{"Flowers", 1},// 14
	{"Cane", 1},// 15
	{"Grenade", 10},// 16
	{"Tear Gas", 10},// 17
	{"Molotov Cocktail", 10},// 18
	{"", 0},// 19
	{"", 0},// 20
	{"", 0},// 21
	{"9mm", 50},// 22
	{"Silenced 9mm", 50},// 23
	{"Desert Eagle", 50},// 24
	{"Shotgun", 20},// 25
	{"Sawnoff Shotgun", 20},// 26
	{"Combat Shotgun", 20},// 27
	{"Micro SMG/Uzi", 200},// 28
	{"MP5", 100},// 29
	{"AK-47", 100},// 30
	{"M4", 100},// 31
	{"Tec-9", 200},// 32
	{"Country Rifle", 10},// 33
	{"Sniper Rifle", 10},// 34
	{"RPG", 10},// 35
	{"HS Rocket", 10},// 36
	{"Flamethrower", 1000},// 37
	{"Minigun", 1000},// 38
	{"Satchel Charge", 10},// 39
	{"Detonator", 0},// 40
	{"Spraycan", 30},// 41
	{"Fire Extinguisher", 500},// 42
	{"Camera", 10},// 43
	{"Night Vis Goggles", 0},// 44
	{"Thermal Goggles", 0},// 45
	{"Parachute", 1}// 46
};

// Floats
new Float:gasPrice;


// TextDraws
new Text:textDrawClock;