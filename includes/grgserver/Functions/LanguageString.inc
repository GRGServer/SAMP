LanguageString(playerID, stringID)
{
	new string[STRINGLENGTH_LANGUAGESTRING];
	switch (PVar:playerID[LANGUAGE])
	{
		case LANGUAGE_ENGLISH:
		{
			strcat(string, languageStrings[stringID][LANGUAGESTRING_ENGLISH]);
		}
		case LANGUAGE_GERMAN:
		{
			strcat(string, languageStrings[stringID][LANGUAGESTRING_GERMAN]);
		}
	}
	return string;
}