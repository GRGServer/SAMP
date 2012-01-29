public OnFilterScriptInit()
{
	print("Connecting to MySQL server");
	mysql_init(LOG_ALL, true);
	mysql_connect(MYSQL_HOST, MYSQL_USERNAME, MYSQL_PASSWORD, MYSQL_DATABASE);
	print("Connecting to IRC server");
	ircBot = IRC_Connect(IRC_HOST, IRC_PORT, IRC_USERNAME, IRC_USERNAME, IRC_USERNAME, IRC_SSL);
	print("Setting game mode text");
	new string[256];
	format(string, sizeof(string), "GRG Server (SVN Revision %d)", COMPILER_SVN_REVISION);
	SetGameModeText(string);
	print("Starting timers");
	SetTimer("timer_slow", 5000, true);
	print("Adding player classes");
	AddPlayerClass(0, SPAWN_POSX, SPAWN_POSY, SPAWN_POSZ, SPAWN_ANGLE, 0, 0, 0, 0, 0, 0);
	print("Connecting NPCs");
	mysql_query("SELECT * FROM `npcs` WHERE `AutoConnect` = '1'");
	mysql_store_result();
	while (fetchMySQLRow())
	{
		ConnectNPC(getMySQLField("Name"), "npcplayer");
	}
	mysql_free_result();
	print("Complete");
	return true;
}

public OnFilterScriptExit()
{
	print("Disconnecting from MySQL server");
	mysql_close();
	print("Disconnecting from IRC server");
	IRC_Quit(ircBot, "SAMP-Server IRC chat relay");
	print("Complete");
	return true;
}