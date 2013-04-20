LanguageString(playerID, stringName[])
{
	new string[STRINGLENGTH_LANGUAGESTRING];
	if (playerID == INVALID_PLAYER_ID)
	{
		imessage(string, stringName, "en");
	}
	else
	{
		imessage(string, stringName, PVar:playerID[LANGUAGE]);
	}
	if (!StrNotNull(string))
	{
		printf("Invalid language string: %s", stringName);
	}
	string = str_replace("\\n", "\n", string);
	return string;
}