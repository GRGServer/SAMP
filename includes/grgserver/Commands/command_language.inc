CMD:language(playerid, params[], "Switch language")
{
	if (!strcmp(PVar:playerid[LANGUAGE], "de", true))
	{
		format(PVar:playerid[LANGUAGE], STRINGLENGTH_LANGUAGEKEY, "en");
	}
	else
	{
		format(PVar:playerid[LANGUAGE], STRINGLENGTH_LANGUAGEKEY, "de");
	}
	SendClientMessage(playerid, COLOR_INFO, LanguageString(playerid, "Your language has been switched"));
	return COMMAND_OK;
}