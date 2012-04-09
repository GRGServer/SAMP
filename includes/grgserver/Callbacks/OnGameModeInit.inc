public OnGameModeInit()
{
	print("* Loading Gamemode...");
	printf("    SVN Revision: %d", COMPILER_SVN_REVISION);
	printf("    Compile date: %s %s", COMPILER_DATE, COMPILER_TIME);
	printf("    Last committer: %s", COMPILER_SVN_LASTCOMMITTER);
	if (fexist(FILE_LASTCHANGES))
	{
		new logLine[256];
		new File:changesFile = fopen(FILE_LASTCHANGES, io_read);
		fread(changesFile, logLine);// Skip "------------------------------------------------------------------------"
		fread(changesFile, logLine);// Skip "rXXX | user | yyyy-mm-dd hh:ii:ss +xxxx (ddd, dd mmm yyyy) | x line(s)"
		fread(changesFile, logLine);// Skip ""
		print("    SVN Changelog:");
		while (fread(changesFile, logLine))
		{
			RemoveNewLine(logLine);
			if (strlen(logLine) && strcmp(logLine, "------------------------------------------------------------------------"))
			{
				printf("    > %s", logLine);
			}
		}
		fclose(changesFile);
	}
	print("* Defining variables...");
	maxPlayers = GetServerVarAsInt("maxplayers");
	print("* Checking SVN stuff...");
	new File:svnRevisionFile;
	new oldSvnRevision[16];
	if (fexist(FILE_RUNNINGREVISION))
	{
		svnRevisionFile = fopen(FILE_RUNNINGREVISION, io_read);
		if (svnRevisionFile)
		{
			fread(svnRevisionFile, oldSvnRevision, sizeof(oldSvnRevision));
			fclose(svnRevisionFile);
		}
	}
	if (strval(oldSvnRevision) != COMPILER_SVN_REVISION)
	{
		svnRevisionChanged = true;
		svnRevisionFile = fopen(FILE_RUNNINGREVISION, io_write);
		if (svnRevisionFile)
		{
			fwrite(svnRevisionFile, val2str(COMPILER_SVN_REVISION));
			fclose(svnRevisionFile);
		}
	}
	print("* Initializing MySQL connection...");
	new MySQL:mysqlConnection = mysql_init(LOG_ONLY_ERRORS, true);
	switch (GetServerVarAsInt("port"))
	{
		case 7776:
		{
			printf("Connecting to development MySQL database (%s@%s/%s)...", MYSQL_DEV_USERNAME, MYSQL_DEV_HOST, MYSQL_DEV_DATABASE);
			if (!mysql_connect(MYSQL_DEV_HOST, MYSQL_DEV_USERNAME, MYSQL_DEV_PASSWORD, MYSQL_DEV_DATABASE, mysqlConnection, true))
			{
				print("MySQL connection failed!");
				return false;
			}
		}
		case 7777:
		{
			printf("Connecting to public MySQL database (%s@%s/%s)...", MYSQL_PUBLIC_USERNAME, MYSQL_PUBLIC_HOST, MYSQL_PUBLIC_DATABASE);
			if (!mysql_connect(MYSQL_PUBLIC_HOST, MYSQL_PUBLIC_USERNAME, MYSQL_PUBLIC_PASSWORD, MYSQL_PUBLIC_DATABASE, mysqlConnection, true))
			{
				print("MySQL connection failed!");
				return false;
			}
		}
	}
	print("* Connecting to IRC server...");
	ircBot = IRC_Connect(IRC_HOST, IRC_PORT, IRC_USERNAME, IRC_USERNAME, IRC_USERNAME, IRC_SSL);
	print("* Adding dummy player classes...");
	AddPlayerClass(0, SPAWN_POSX, SPAWN_POSY, SPAWN_POSZ, SPAWN_ANGLE, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(0, SPAWN_POSX, SPAWN_POSY, SPAWN_POSZ, SPAWN_ANGLE, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(0, SPAWN_POSX, SPAWN_POSY, SPAWN_POSZ, SPAWN_ANGLE, 0, 0, 0, 0, 0, 0);
	ReloadLanguageStrings();
	ReloadObjects();
	ReloadVehicleModels();
	ReloadSavedVehicles();
	ReloadPickups();
	CreateGlobalTextDraws();
	print("* Doing misc stuff...");
	FormatNew:gameModeTextString[30]("GRG Server r%d", COMPILER_SVN_REVISION);
	SetGameModeText(gameModeTextString);
	EnableStuntBonusForAll(false);
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
	DisableInteriorEnterExits();
	Streamer_VisibleItems(STREAMER_TYPE_OBJECT, MAX_OBJECTS);
	UpdateGasPrice();
	print("* Starting timers...");
	StartTimer:EVERYMINUTE("Timer_EveryMinute", true);
	StartTimer:FAST("Timer_Fast", true);
	StartTimer:HOURLY("Timer_Hourly", true);
	StartTimer:SLOW("Timer_Slow", true);
	StartTimer:STABLECHECK("Timer_StableCheck", false);
	ReconnectNPCs();
	return true;
}