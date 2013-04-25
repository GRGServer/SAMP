CMD:me(playerid, params[], StringID:109("Say what you do (e.g. '/me follows an admin' will be shown to all players as '* <Your name> follows an admin')"))
{
	if (strlen(params))
	{
		new string[256];
		Format:string("*%s %s", GetPlayerNameEx(playerid), params);
		SendClientMessageToAll(COLOR_ME, string);
		return COMMAND_OK;
	}
	else
	{
		CmdUsageMsg(playerid, "me", "Text");
		return COMMAND_USAGE;
	}
}