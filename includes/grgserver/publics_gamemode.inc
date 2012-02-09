public OnGameModeInit()
{
	print("Connecting to MySQL server...");
	new MySQL:mysqlConnection = mysql_init(LOG_ONLY_ERRORS, true);
	mysql_connect(MYSQL_HOST, MYSQL_USERNAME, MYSQL_PASSWORD, MYSQL_DATABASE, mysqlConnection, true);
	print("Connecting to IRC server...");
	ircBot = IRC_Connect(IRC_HOST, IRC_PORT, IRC_USERNAME, IRC_USERNAME, IRC_USERNAME, IRC_SSL);
	print("Starting timers...");
	SetTimer("timer_slow", 5000, true);
	print("Adding player classes...");
	AddPlayerClass(0, SPAWN_POSX, SPAWN_POSY, SPAWN_POSZ, SPAWN_ANGLE, 0, 0, 0, 0, 0, 0);
	print("Connecting NPCs...");
	mysql_query("SELECT * FROM `npcs` WHERE `AutoConnect` = '1'");
	mysql_store_result();
	while (fetchMySQLRow())
	{
		ConnectNPC(getMySQLField("Name"), "npcplayer");
	}
	mysql_free_result();
	print("Spawing saved vehicles...");
	mysql_query("SELECT * FROM `savedvehicles`");
	mysql_store_result();
	while (fetchMySQLRow())
	{
		new vehicleID = CreateVehicle(strval(getMySQLField("ModelID")), floatstr(getMySQLField("PosX")), floatstr(getMySQLField("PosY")), floatstr(getMySQLField("PosZ")), floatstr(getMySQLField("Angle")), random(126), random(126), -1);
		vehicles[vehicleID] = strval(getMySQLField("ID"));
		LinkVehicleToInterior(vehicleID, strval(getMySQLField("Interior")));
	}
	mysql_free_result();
	print("Doing misc stuff...");
	new string[256];
	format(string, sizeof(string), "GRG Server r%d", COMPILER_SVN_REVISION);
	SetGameModeText(string);
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
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		Tacho[i] = TextDrawCreate(510, 370, "Km/h:---");
		TextDrawLetterSize(Tacho[i], 0.4, 1.1);
		TextDrawFont(Tacho[i], 1);
		TextDrawSetShadow(Tacho[i], 2);
		TextDrawSetOutline(Tacho[i],1);
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
