CMD:language(playerid, params[], 8)
{
	if (!strcmp(PVar:playerid[LANGUAGE], "de", true))
	{
		PVar:playerid[LANGUAGE] = "en";
	}
	else
	{
		PVar:playerid[LANGUAGE] = "de";
	}
	ReloadTextDraws(playerid);
	SendClientMessageEx(playerid, COLOR_INFO, 24);
	return COMMAND_OK;
}