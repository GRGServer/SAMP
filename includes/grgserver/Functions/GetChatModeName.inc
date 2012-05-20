GetChatModeName(playerID, chatMode[])
{
	new name[30];
	if (IsStr(chatMode, "ADMINS"))
	{
		strcat(name, "Admins");
	}
	if (IsStr(chatMode, "ALL"))
	{
		strcat(name, LanguageString(playerID, 310));
	}
	if (IsStr(chatMode, "FRIENDS"))
	{
		strcat(name, LanguageString(playerID, 453));
	}
	if (IsStr(chatMode, "INRANGE"))
	{
		strcat(name, LanguageString(playerID, 311));
	}
	if (IsStr(chatMode, "JOB"))
	{
		strcat(name, "Job");
	}
	return name;
}