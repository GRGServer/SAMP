CMD:language(playerid, params[], 8)
{
	if (PVar:playerid[LANGUAGE] == LANGUAGE_GERMAN)
	{
		PVar:playerid[LANGUAGE] = LANGUAGE_ENGLISH;
	}
	else
	{
		PVar:playerid[LANGUAGE] = LANGUAGE_GERMAN;
	}
	ReloadTextDraws(playerid);
	SendClientMessageEx(playerid, COLOR_INFO, 24);
	return COMMAND_OK;
}