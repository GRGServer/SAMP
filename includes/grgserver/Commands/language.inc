CMD:language(playerid, params[], StringID:8("Switch language"))
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
	SendClientMessageEx(playerid, COLOR_INFO, StringID:24("Your language has been switched"));
	return COMMAND_OK;
}