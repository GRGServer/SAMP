public OnFilterScriptInit()
{
	print("Loading GRG Script");
	print("Connecting to MySQL server");
	mysql_connect(MYSQL_HOST, MYSQL_USERNAME, MYSQL_DATABASE, MYSQL_PASSWORD);
	print("Connecting to IRC server");
	ircBot = IRC_Connect(IRC_HOST, IRC_PORT, IRC_USERNAME, IRC_USERNAME, IRC_USERNAME, IRC_SSL);
	new string[256];
	format(string, sizeof(string), "GRG Server (SVN Revision %d)", SVN_REVISION);
	SetGameModeText(string);
	AddPlayerClass(0, SPAWN_POSX, SPAWN_POSY, SPAWN_POSZ, SPAWN_ANGLE, 0, 0, 0, 0, 0, 0);
	print("Cnonecting NPCs");
	mysql_query("SELECT * FROM `npcs` WHERE `AutoConnect` = '1'");
	/*mysql_store_result();
	while (mysql_retrieve_row())
	{
		ConnectNPC(getMySQLField("Name"), "npcplayer");
	}
	mysql_free_result();*/
	print("GRG Script loaded");
	return true;
}

public OnFilterScriptExit()
{
	mysql_close();
	IRC_Quit(ircBot, "SAMP-Server IRC chat relay");
	return true;
}