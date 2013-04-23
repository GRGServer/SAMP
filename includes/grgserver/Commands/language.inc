CMD:language(playerid, params[], StringID:8(""))
{
	if (PVar:playerid[LANGUAGE] == LANGUAGE_ENGLISH)
	{
		PVar:playerid[LANGUAGE] = LANGUAGE_GERMAN;
	}
	else
	{
		PVar:playerid[LANGUAGE] = LANGUAGE_ENGLISH;
	}
	ReloadTextDraws(playerid);
	SendClientMessageEx(playerid, COLOR_INFO, StringID:24(""));
	return COMMAND_OK;
}