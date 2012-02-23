public OnGameModeInit()
{
	new File:svnRevisionFile;
	new oldSvnRevision[256];
	print("* Loading Gamemode...");
	printf("    SVN Revision: %d", COMPILER_SVN_REVISION);
	printf("    Compile date: %s %s", COMPILER_DATE, COMPILER_TIME);
	printf("    Last committer: %s", COMPILER_SVN_LASTCOMMITTER);
	print("* Checking SVN stuff...");
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
	print("* Connecting to MySQL server...");
	new MySQL:mysqlConnection = mysql_init(LOG_ONLY_ERRORS, true);
	mysql_connect(MYSQL_HOST, MYSQL_USERNAME, MYSQL_PASSWORD, MYSQL_DATABASE, mysqlConnection, true);
	print("* Connecting to IRC server...");
	ircBot = IRC_Connect(IRC_HOST, IRC_PORT, IRC_USERNAME, IRC_USERNAME, IRC_USERNAME, IRC_SSL);
	print("* Adding dummy player classes...");
	AddPlayerClass(0, SPAWN_POSX, SPAWN_POSY, SPAWN_POSZ, SPAWN_ANGLE, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(0, SPAWN_POSX, SPAWN_POSY, SPAWN_POSZ, SPAWN_ANGLE, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(0, SPAWN_POSX, SPAWN_POSY, SPAWN_POSZ, SPAWN_ANGLE, 0, 0, 0, 0, 0, 0);
	print("* Loading vehicle models...");
	ReloadVehicleModels();
	print("* Loading saved vehicles...");
	ReloadSavedVehicles();
	print("* Creating pickups...");
	ReloadPickups();
	print("* Creating server wide TextDraws...");
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
	print("* Doing misc stuff...");
	new gameModeTextString[256];
	format(gameModeTextString, sizeof(gameModeTextString), "GRG Server r%d", COMPILER_SVN_REVISION);
	SetGameModeText(gameModeTextString);
	DisableInteriorEnterExits();
	UpdateGasPrice();
	print("* Starting timers...");
	StartTimer:EveryMinute[EVERYMINUTE](true);
	StartTimer:Fast[FAST](true);
	StartTimer:Hourly[HOURLY](true);
	StartTimer:Slow[SLOW](true);
	StartTimer:StableCheck[STABLECHECK](false);
	print("* Connecting NPCs...");
	ReconnectNPCs();
	return true;
}

public OnGameModeExit()
{
	print("* Unloading Gamemode...");
	print("* Saving players...");
	for (new playerID = 0; playerID < MAX_PLAYERS; playerID++)
	{
		if (IsPlayerNPC(playerID))
		{
			Kick(playerID);
		}
		else
		{
			SavePlayer(playerID);
		}
	}
	print("* Saving vehicles...");
	for (new vehicleID = 0; vehicleID < MAX_VEHICLES; vehicleID++)
	{
		SaveVehicle(vehicleID, 0);// TODO: Get interior of the vehicle?
	}
	print("* Disconnecting from MySQL server...");
	mysql_close();
	print("* Disconnecting from IRC server...");
	IRC_Quit(ircBot, "SAMP-Server IRC chat relay");
	print("* Gamemode will now end");
	return true;
}