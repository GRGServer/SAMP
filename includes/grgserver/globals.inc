// Variables
new addLineString[256];
new clientMessageString[256];
new distanceCalcArray[MAX_DISTANCECALCELEMENTS][enum_distanceCalc];
new languageStrings[LANGUAGE_MAXSTRINGS][enum_languageString];
new maxPlayers;
new musicSoundIDs[] = {1062, 1068, 1076, 1097, 1183, 1185, 1187};
new naviTargets[MAX_PLAYERS][MAX_NAVITARGETS][enum_naviTarget];
new oldHour = -1;
new oldMinute = -1;
new permissions[MAX_PLAYERS][enum_permission];
new pickupLoader[MAX_PICKUPS][enum_pickupLoader];
new pickups[MAX_PICKUPS][enum_pickup];
new playerVariables[MAX_PLAYERS][enum_playerVariable];
new sqlQuery[1024];
new vehicles[MAX_VEHICLES][enum_vehicle];
new vehicleLightObjects[MAX_VEHICLES][enum_neonType][LIGHTOBJECT_MAXCOLORS];
new vehicleModels[212][enum_vehicleModel];
new weapons[47][enum_weapon];
new zones[365][enum_zone];


// Floats
new Float:gasPrice;


// TextDraws
new Text:textDrawClock;