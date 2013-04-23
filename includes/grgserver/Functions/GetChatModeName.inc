GetChatModeName(playerID, chatMode[])
{
	new name[30];
	if (IsStr(chatMode, "ADMINS"))
	{
		strcat(name, "Admins");
	}
	if (IsStr(chatMode, "ALL"))
	{
		strcat(name, LanguageString(playerID, StringID:310("")));
	}
	if (IsStr(chatMode, "INRANGE"))
	{
		strcat(name, LanguageString(playerID, StringID:311("")));
	}
	if (IsStr(chatMode, "JOB"))
	{
		strcat(name, "Job");
	}
	if (IsStr(chatMode, "PLAYER"))
	{
		strcat(name, LanguageString(playerID, StringID:178("")));
	}
	return name;
}