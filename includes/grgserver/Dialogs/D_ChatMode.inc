ShowDialog:ChatMode(playerID)
{
	new options[1024];
	AddLine(options, LanguageString(playerID, 311));
	AddLine(options, LanguageString(playerID, 310));
	AddLine(options, LanguageString(playerID, 504));
	AddLine(options, "Job");
	AddLine(options, "Admins");
	CreateDialog(playerID, "ChatMode", DIALOG_STYLE_LIST, LanguageString(playerID, 312), options, "OK", LanguageString(playerID, 165));
}

DialogResponse:ChatMode(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new oldChatMode[STRINGLENGTH_CHATMODE];
		strcat(oldChatMode, PVar:playerID[CHATMODE]);
		if (IsStr(inputText, "Admins"))
		{
			SetPVarStr:playerID[CHATMODE][STRINGLENGTH_CHATMODE]("ADMINS");
		}
		if (IsStr(inputText, LanguageString(playerID, 310)))
		{
			SetPVarStr:playerID[CHATMODE][STRINGLENGTH_CHATMODE]("ALL");
		}
		if (IsStr(inputText, LanguageString(playerID, 504)))
		{
			ShowDialog:ChatMode_FriendList(playerID);
		}
		if (IsStr(inputText, LanguageString(playerID, 311)))
		{
			SetPVarStr:playerID[CHATMODE][STRINGLENGTH_CHATMODE]("INRANGE");
		}
		if (IsStr(inputText, "Job"))
		{
			SetPVarStr:playerID[CHATMODE][STRINGLENGTH_CHATMODE]("JOB");
		}
		if (!IsStr(oldChatMode, PVar:playerID[CHATMODE]))
		{
			SendClientMessageEx(playerID, COLOR_INFO, 313, GetChatModeName(playerID, PVar:playerID[CHATMODE]));
		}
	}
}