LanguageString(playerID, englishString[])
{
	new string[256];
	if (!strcmp(PVar:playerID[LANGUAGE], "de", true))
	{
		Format:string(GetMySQLValue("languagestrings", "German", "English", englishString));
	}
	if (!strlen(string))
	{
		Format:string(englishString);
	}
	return string;
}