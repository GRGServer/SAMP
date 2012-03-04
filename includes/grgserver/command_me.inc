CMD:me(playerid, params[], "Sagen, was du machst (z.B. '/me rennt Admin hinterher' sehen alle Spieler als '*<Dein Name> rennt Admin hinterher')")
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