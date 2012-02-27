// Variables
new ircBot;
new svnRevisionChanged;
new Float:gasPrice;
new Text:textDrawSpeedoColumn1;
new Text:textDrawClock;


// Strings
new sqlQuery[1024];


// Arrays
new vehicles[MAX_VEHICLES][enum_vehicle];
new vehicleModels[212][enum_vehicleModel];
new pickups[MAX_PICKUPS][enum_pickup];
new pickupLoader[MAX_PICKUPS][enum_pickupLoader];
new permissions[MAX_PLAYERS][enum_permission];
new savePlayers[MAX_PLAYERS];
new Text:textDrawSpeedoColumn2[MAX_PLAYERS];
new Text:textDrawRadioStation[MAX_PLAYERS];