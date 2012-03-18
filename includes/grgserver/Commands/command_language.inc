CMD:language(playerid, params[], 8)
{
	if (!strcmp(PVar:playerid[LANGUAGE], "de", true))
	{
		format(PVar:playerid[LANGUAGE], STRINGLENGTH_LANGUAGEKEY, "en");
	}
	else
	{
		format(PVar:playerid[LANGUAGE], STRINGLENGTH_LANGUAGEKEY, "de");
	}
	ReloadTextDraws(playerid);
	SendClientMessageEx(playerid, COLOR_INFO, 24);
	return COMMAND_OK;
}