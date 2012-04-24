// Variables
new clientMessageString[256];
new ircBot;
new languageStrings[LANGUAGE_MAXSTRINGS][enum_languageString];
new maxPlayers;
new permissions[MAX_PLAYERS][enum_permission];
new pickupLoader[MAX_PICKUPS][enum_pickupLoader];
new pickups[MAX_PICKUPS][enum_pickup];
new playerVariables[MAX_PLAYERS][enum_playerVariable];
new sqlQuery[1024];
new svnRevisionChanged;
new vehicles[MAX_VEHICLES][enum_vehicle];
new vehicleModels[212][enum_vehicleModel];


// Floats
new Float:gasPrice;


// TextDraws
new Text:textDrawClock;