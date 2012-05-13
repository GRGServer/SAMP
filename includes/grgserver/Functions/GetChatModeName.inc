GetChatModeName(playerID, chatMode)
{
	new name[30];
	switch (chatMode)
	{
		case CHATMODE_ADMINS:
		{
			strcat(name, "Admins");
		}
		case CHATMODE_ALL:
		{
			strcat(name, LanguageString(playerID, 310));
		}
		case CHATMODE_INRANGE:
		{
			strcat(name, LanguageString(playerID, 311));
		}
		case CHATMODE_JOB:
		{
			strcat(name, "Job");
		}
	}
	return name;
}