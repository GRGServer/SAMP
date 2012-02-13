public OnGameModeInit()
{
	new gameModeTextString[256];
	format(gameModeTextString, sizeof(gameModeTextString), "GRG Server r%d", COMPILER_SVN_REVISION);
	print("Connecting to MySQL server...");
	new MySQL:mysqlConnection = mysql_init(LOG_ONLY_ERRORS, true);
	mysql_connect(MYSQL_HOST, MYSQL_USERNAME, MYSQL_PASSWORD, MYSQL_DATABASE, mysqlConnection, true);
	print("Connecting to IRC server...");
	ircBot = IRC_Connect(IRC_HOST, IRC_PORT, IRC_USERNAME, IRC_USERNAME, IRC_USERNAME, IRC_SSL);
	print("Starting timers...");
	SetTimer("timer_fast", TIMER_FAST, true);
	SetTimer("timer_slow", TIMER_SLOW, true);
	SetTimer("timer_hourly", TIMER_HOURLY, true);
	print("Adding player classes...");
	AddPlayerClass(0, SPAWN_POSX, SPAWN_POSY, SPAWN_POSZ, SPAWN_ANGLE, 0, 0, 0, 0, 0, 0);
	print("Connecting NPCs...");
	mysql_query("SELECT * FROM `npcs` WHERE `AutoConnect` = '1'");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		ConnectNPC(GetMySQLField("Name"), "npcplayer");
	}
	mysql_free_result();
	print("Loading vehicle models...");
	mysql_query("SELECT * FROM `vehiclemodels`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new index = strval(GetMySQLField("ModelID")) - 400;
		vehicleModels[index][vehicleModels_fuelUsage] = floatstr(GetMySQLField("FuelUsage"));
		vehicleModels[index][vehicleModels_maxFuel] = floatstr(GetMySQLField("MaxFuel"));
	}
	mysql_free_result();
	print("Loading saved vehicles...");
	mysql_query("SELECT * FROM `savedvehicles`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new vehicleID = CreateVehicle(strval(GetMySQLField("ModelID")), floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")), floatstr(GetMySQLField("Angle")), random(126), random(126), -1);
		vehicles[vehicleID][vehicles_saveID] = strval(GetMySQLField("ID"));
		vehicles[vehicleID][vehicles_currentFuel] = floatstr(GetMySQLField("CurrentFuel"));
		LinkVehicleToInterior(vehicleID, strval(GetMySQLField("Interior")));
	}
	mysql_free_result();
	print("Creating pickups...");
	mysql_query("SELECT * FROM `pickups`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new modelID = -1;
		new type;
		new pickup;
		switch (strval(GetMySQLField("Type")))
		{
			case PICKUPTYPE_GASSTATION:
			{
				modelID = PICKUP_GASSTATION;
				type = 23;
			}
		}
		if (modelID == -1)
		{
			printf("Invalid pickup type: %d", strval(GetMySQLField("Type")));
		}
		else
		{
			pickup = CreatePickup(modelID, type, floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")));
			pickups[pickup][pickups_type] = strval(GetMySQLField("Type"));
		}
	}
	mysql_free_result();
	print("Creating server wide TextDraws...");
	textDrawSpeedoColumn1 = TextDrawCreate(480, 400, "Geschwindigkeit:~n~Zustand:~n~Tank:~n~Verbrauch/100km:");
	TextDrawAlignment(textDrawSpeedoColumn1, 1);
	TextDrawLetterSize(textDrawSpeedoColumn1, 0.3, 0.9);
	TextDrawFont(textDrawSpeedoColumn1, 1);
	TextDrawSetShadow(textDrawSpeedoColumn1, 2);
	TextDrawTextSize(textDrawSpeedoColumn1, 635, 475);
	TextDrawBoxColor(textDrawSpeedoColumn1, 0x00000080);
	TextDrawUseBox(textDrawSpeedoColumn1, true);
	textDrawClock = TextDrawCreate(547, 25, "_");
	TextDrawSetShadow(textDrawClock, 0);
	TextDrawSetOutline(textDrawClock, 2);
	TextDrawLetterSize(textDrawClock, 0.6, 1.8);
	TextDrawFont(textDrawClock, 3);
	textDrawBottomBanner = TextDrawCreate(0, 440, gameModeTextString);
	TextDrawLetterSize(textDrawBottomBanner, 0.3, 0.9);
	TextDrawFont(textDrawBottomBanner, 1);
	TextDrawSetShadow(textDrawBottomBanner, 2);
	TextDrawTextSize(textDrawBottomBanner, 640, 480);
	TextDrawBoxColor(textDrawBottomBanner, 0x00000080);
	TextDrawUseBox(textDrawBottomBanner, true);
	print("Doing misc stuff...");
	SetGameModeText(gameModeTextString);
	new File:svnRevisionFile;
	new oldSvnRevision[256];
	if (fexist("svn_revision"))
	{
		svnRevisionFile = fopen("svn_revision", io_read);
		if (svnRevisionFile)
		{
			fread(svnRevisionFile, oldSvnRevision, sizeof(oldSvnRevision));
			fclose(svnRevisionFile);
		}
	}
	if (strval(oldSvnRevision) != COMPILER_SVN_REVISION)
	{
		svnRevisionChanged = true;
		svnRevisionFile = fopen("svn_revision", io_write);
		if (svnRevisionFile)
		{
			fwrite(svnRevisionFile, val2str(COMPILER_SVN_REVISION));
			fclose(svnRevisionFile);
		}
	}
	UpdateGasPrice();
	print("Gamemode loading complete");
	return true;
}

public OnGameModeExit()
{
	print("Disconnecting from MySQL server...");
	mysql_close();
	print("Disconnecting from IRC server...");
	IRC_Quit(ircBot, "SAMP-Server IRC chat relay");
	print("Gamemode unloading complete");
	return true;
}