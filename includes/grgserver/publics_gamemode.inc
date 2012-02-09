public OnGameModeInit()
{
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
	print("Spawing saved vehicles...");
	mysql_query("SELECT * FROM `savedvehicles`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new vehicleID = CreateVehicle(strval(GetMySQLField("ModelID")), floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")), floatstr(GetMySQLField("Angle")), random(126), random(126), -1);
		vehicles[vehicleID] = strval(GetMySQLField("ID"));
		LinkVehicleToInterior(vehicleID, strval(GetMySQLField("Interior")));
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
