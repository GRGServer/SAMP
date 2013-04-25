ShowDialog:ChatMode(playerID)
{
	new options[1024];
	AddLine(options, LanguageString(playerID, StringID:311("In range (max 100m)")));
	AddLine(options, LanguageString(playerID, StringID:310("All")));
	AddLine(options, LanguageString(playerID, StringID:504("Friend")));
	AddLine(options, "Job");
	AddLine(options, "Admins");
	CreateDialog(playerID, "ChatMode", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:312("Change chat channel")), options, "OK", LanguageString(playerID, StringID:165("Cancel")));
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
		if (IsStr(inputText, LanguageString(playerID, StringID:310("All"))))
		{
			SetPVarStr:playerID[CHATMODE][STRINGLENGTH_CHATMODE]("ALL");
		}
		if (IsStr(inputText, LanguageString(playerID, StringID:504("Friend"))))
		{
			ShowDialog:ChatMode_FriendList(playerID);
		}
		if (IsStr(inputText, LanguageString(playerID, StringID:311("In range (max 100m)"))))
		{
			SetPVarStr:playerID[CHATMODE][STRINGLENGTH_CHATMODE]("INRANGE");
		}
		if (IsStr(inputText, "Job"))
		{
			SetPVarStr:playerID[CHATMODE][STRINGLENGTH_CHATMODE]("JOB");
		}
		if (!IsStr(oldChatMode, PVar:playerID[CHATMODE]))
		{
			SendClientMessageEx(playerID, COLOR_INFO, StringID:313("Chat channel changed to '%s'"), GetChatModeName(playerID, PVar:playerID[CHATMODE]));
		}
	}
}