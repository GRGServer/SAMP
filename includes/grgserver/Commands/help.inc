CMD:help(playerid, params[], StringID:107("Show help"))
{
	SendClientMessageEx(playerid, COLOR_INFO, StringID:82("Use /cmds to see a list of commands"));
	return COMMAND_OK;
}