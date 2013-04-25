GetChatModeName(playerID, chatMode[])
{
	new name[30];
	if (IsStr(chatMode, "ADMINS"))
	{
		strcat(name, "Admins");
	}
	if (IsStr(chatMode, "ALL"))
	{
		strcat(name, LanguageString(playerID, StringID:310("All")));
	}
	if (IsStr(chatMode, "INRANGE"))
	{
		strcat(name, LanguageString(playerID, StringID:311("In range (max 100m)")));
	}
	if (IsStr(chatMode, "JOB"))
	{
		strcat(name, "Job");
	}
	if (IsStr(chatMode, "PLAYER"))
	{
		strcat(name, LanguageString(playerID, StringID:178("Player")));
	}
	return name;
}