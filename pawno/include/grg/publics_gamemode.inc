public OnGameModeInit()
{
	mysql_init();
	mysql_connect(MYSQL_HOST, MYSQL_USERNAME, MYSQL_PASSWORD, MYSQL_DATABASE);
	ircBot = IRC_Connect(IRC_HOST, IRC_PORT, IRC_USERNAME, IRC_USERNAME, IRC_USERNAME, IRC_SSL);
	SetGameModeText("GRG Server");
	AddPlayerClass(0, SPAWN_POSX, SPAWN_POSY, SPAWN_POSZ, SPAWN_ANGLE, 0, 0, 0, 0, 0, 0);
	return true;
}

public OnGameModeExit()
{
	mysql_close();
	IRC_Quit(ircBot, "SAMP-Server IRC chat relay");
	return true;
}