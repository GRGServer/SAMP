new addLineString[256];
new clientMessageString[256];
new distanceCalcArray[MAX_DISTANCECALCELEMENTS][enum_distanceCalc];
new dynamicObjects[MAX_DYNAMIC_OBJECTS][enum_object];
new languageStrings[MAX_LANGUAGE_STRINGS][enum_languageString];
new maxPlayers;
new naviTargets[MAX_PLAYERS][MAX_NAVITARGETS][enum_naviTarget];
new nextDynamicObjectID;
new objectModels[MAX_OBJECTMODELID][STRINGLENGTH_OBJECTMODELNAME];
new oldHour = -1;
new oldMinute = -1;
new permissions[MAX_PLAYERS][enum_permission];
new pickupLoader[MAX_PICKUPS][enum_pickupLoader];
new pickups[MAX_PICKUPS][enum_pickup];
new playerVariables[MAX_PLAYERS][enum_playerVariable];
new speedCameras[MAX_SPEEDCAMERAS][enum_speedCamera];
new sqlQuery[1024];
new vehicles[MAX_VEHICLES][enum_vehicle];
new vehicleLightObjects[MAX_VEHICLES][enum_neonType][LIGHTOBJECT_MAXCOLORS];
new vehicleModels[212][enum_vehicleModel];
new weapons[47][enum_weapon];
new zones[365][enum_zone];

new Float:gasPrice;

new Text:decimalPoint;
new Text:textDrawClock;