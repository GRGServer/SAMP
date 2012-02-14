// Variables
new ircBot;
new svnRevisionChanged;
new Float:gasPrice;
new Text:textDrawSpeedoColumn1;
new Text:textDrawClock;
new Text:textDrawBottomBanner;
new Text:LIVE;
new Text:YOUFM;
new Text:YOUFM2;
new Text:YOUFM3;
new Text:YOUFM4;
new Text:RTL;
new Text:RADIOAUS;
new Text:radioplanet;
new Text:technobase;
new timer_radio;


// Arrays
new vehicles[MAX_VEHICLES][enum_vehicles];
new vehicleModels[212][enum_vehicleModels];
new houses[MAX_PLAYERS][enum_houses];
new pickups[MAX_PICKUPS][enum_pickups];
new Text:textDrawSpeedoColumn2[MAX_PLAYERS];
new channels[MAX_VEHICLES];
new closed[MAX_PLAYERS];