CMD:language(playerid, params[], 8)
{
	if (strcmp(PVar:playerid[LANGUAGE], "de"))
	{
		PVar:playerid[LANGUAGE] = "de";
	}
	else
	{
		PVar:playerid[LANGUAGE] = "en";
	}
	ReloadTextDraws(playerid);
	SendClientMessageEx(playerid, COLOR_INFO, "24");
	return COMMAND_OK;
}