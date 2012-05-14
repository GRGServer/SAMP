ShowDialog:CHATMODE(playerID)
{
	new options[1024];
	AddLine(options, LanguageString(playerID, 311));
	AddLine(options, LanguageString(playerID, 310));
	AddLine(options, "Job");
	AddLine(options, "Admins");
	CreateDialog(playerID, "CHATMODE", DIALOG_STYLE_LIST, LanguageString(playerID, 312), options, "OK", LanguageString(playerID, 165));
}

DialogResponse:CHATMODE(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (IsStr(inputText, LanguageString(playerID, 311)))
		{
			PVar:playerID[CHATMODE] = CHATMODE_INRANGE;
		}
		if (IsStr(inputText, LanguageString(playerID, 310)))
		{
			PVar:playerID[CHATMODE] = CHATMODE_ALL;
		}
		if (IsStr(inputText, "Job"))
		{
			PVar:playerID[CHATMODE] = CHATMODE_JOB;
		}
		if (IsStr(inputText, "Admins"))
		{
			PVar:playerID[CHATMODE] = CHATMODE_ADMINS;
		}
		SendClientMessageEx(playerID, COLOR_INFO, 313, GetChatModeName(playerID, PVar:playerID[CHATMODE]));
	}
}