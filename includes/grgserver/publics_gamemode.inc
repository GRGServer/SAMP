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
		vehicleModels[index][vehicleModels_maxFuel] = strval(GetMySQLField("MaxFuel"));
	}
	mysql_free_result();
	print("Spawing saved vehicles...");
	mysql_query("SELECT * FROM `savedvehicles`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new vehicleID = CreateVehicle(strval(GetMySQLField("ModelID")), floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")), floatstr(GetMySQLField("Angle")), random(126), random(126), -1);
		vehicles[vehicleID][vehicles_saveID] = strval(GetMySQLField("ID"));
		vehicles[vehicleID][vehicles_currentFuel] = strval(GetMySQLField("CurrentFuel"));
		LinkVehicleToInterior(vehicleID, strval(GetMySQLField("Interior")));
	}
	mysql_free_result();
	print("Create Pickups ....");
	AddStaticPickup(TankPickup, 1, 1007.3973, -939.7044, 41.8622, -1); // Tanke 1 1 
	AddStaticPickup(TankPickup, 1, 1001.3943, -940.4099, 41.8622, -1); // Tanke 1 2
	AddStaticPickup(TankPickup, 1, 1000.2619, -934.4082, 41.8630, -1); // Tanke 1 3
	AddStaticPickup(TankPickup, 1, 1006.7959, -933.5510, 41.8617, -1); // Tanke 1 4
	AddStaticPickup(TankPickup, 1, 1938.5857, -1769.5831, 13.0657, -1); // Tanke 2 1
	AddStaticPickup(TankPickup, 1, 1938.9346, -1776.5620, 13.0685, -1); // Tanke 2 2
	AddStaticPickup(TankPickup, 1, 1944.6791, -1776.5665, 13.0730, -1); // Tanke 2 3
	AddStaticPickup(TankPickup, 1, 1944.3734, -1769.3955, 13.0710, -1); // Tanke 2 4
	AddStaticPickup(TankPickup, 1, -95.5256, -1160.1895, 1.8353, -1); // Tanke 3 1
	AddStaticPickup(TankPickup, 1, -99.6199, -1169.6541, 2.2372, -1); // Tanke 3 2
	AddStaticPickup(TankPickup, 1, -88.4311, -1162.5652, 1.8875, -1); // Tanke 3 3
	AddStaticPickup(TankPickup, 1, -92.8111, -1173.7557, 1.9817, -1); // Tanke 3 4
	AddStaticPickup(TankPickup, 1, -87.3871, -1178.1429, 1.7402, -1); // Tanke 3 5
	AddStaticPickup(TankPickup, 1, -82.8288, -1166.9786, 1.9123, -1); // Tanke 3 6
	AddStaticPickup(TankPickup, 1, -2024.0704, 155.0165, 28.5182, -1); // Tanke 4 1
	AddStaticPickup(TankPickup, 1, -2029.5110, 155.6705, 28.5182, -1); // Tanke 4 2
	AddStaticPickup(TankPickup, 1, 2210.8625, 2470.1577, 10.5033, -1); // Tanke 5 1
	AddStaticPickup(TankPickup, 1, 2210.6694, 2474.1685, 10.5026, -1); // Tanke 5 2
	AddStaticPickup(TankPickup, 1, 2210.3918, 2479.9395, 10.5026, -1); // Tanke 5 3
	AddStaticPickup(TankPickup, 1, 2204.6409, 2479.2827, 10.5023, -1); // Tanke 5 4
	AddStaticPickup(TankPickup, 1, 2204.6619, 2474.7517, 10.5033, -1); // Tanke 5 5
	AddStaticPickup(TankPickup, 1, 2204.6833, 2470.0627, 10.5021, -1); // Tanke 5 6
	AddStaticPickup(TankPickup, 1, 2193.9958, 2469.8635, 10.5016, -1); // Tanke 5 7
	AddStaticPickup(TankPickup, 1, 2194.2795, 2474.7878, 10.5021, -1); // Tanke 5 8
	AddStaticPickup(TankPickup, 1, 2194.5557, 2480.1274, 10.5034, -1); // Tanke 5 9
	AddStaticPickup(TankPickup, 1, 2199.7302, 2481.4514, 10.5023, -1); // Tanke 5 10
	AddStaticPickup(TankPickup, 1, 2199.9343, 2475.6755, 10.5026, -1); // Tanke 5 11
	AddStaticPickup(TankPickup, 1, 2199.9951, 2470.6389, 10.5031, -1); // Tanke 5 12
	AddStaticPickup(TankPickup, 1, 2120.1875, 927.6614, 10.5019, -1); // Tanke 6 1
	AddStaticPickup(TankPickup, 1, 2115.5586, 927.5698, 10.5026, -1); // Tanke 6 2
	AddStaticPickup(TankPickup, 1, 2109.7017, 927.6696, 10.5027, -1); // Tanke 6 3
	AddStaticPickup(TankPickup, 1, 2108.9758, 917.4871, 10.5022, -1); // Tanke 6 4
	AddStaticPickup(TankPickup, 1, 2114.6011, 917.4871, 10.5040, -1); // Tanke 6 5
	AddStaticPickup(TankPickup, 1, 2120.5237, 917.4871, 10.5025, -1); // Tanke 6 6
	AddStaticPickup(TankPickup, 1, 2121.2354, 912.3043, 10.5020, -1); // Tanke 6 7
	AddStaticPickup(TankPickup, 1, 2115.1841, 911.9506, 10.5039, -1); // Tanke 6 8
	AddStaticPickup(TankPickup, 1, 2108.4514, 911.8604, 10.5046, -1); // Tanke 6 9
	AddStaticPickup(TankPickup, 1, 2109.6018, 923.1636, 10.5033, -1); // Tanke 6 10
	AddStaticPickup(TankPickup, 1, 2115.0156, 923.3151, 10.5023, -1); // Tanke 6 11
	AddStaticPickup(TankPickup, 1, 2121.4531, 923.4949, 10.5025, -1); // Tanke 6 12
	print("Create Pickups Done!");
	print("Creating server wide TextDraws...");
	textDrawSpeedoColumn1 = TextDrawCreate(490, 400, "Geschwindigkeit:~n~Zustand:~n~Tank:");
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