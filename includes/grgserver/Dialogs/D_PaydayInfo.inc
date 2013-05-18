ShowDialog:PaydayInfo(playerID)
{
	new difference = GetOnlineTime(playerID) - PVar:playerID[LASTPAYDAY];
	new string[256];
	AddLine:string(LanguageString(playerID, StringID:421("Time elapsed since the last pay day: %s")), FormatTime(difference));
	AddLine:string(LanguageString(playerID, StringID:422("Time till the next pay day: %s")), FormatTime(PAYDAY_INTERVAL - difference));
	CreateDialog(playerID, "PaydayInfo", DIALOG_STYLE_MSGBOX, LanguageString(playerID, StringID:423("Information about the pay day")), string, "OK", "");
}

DialogResponse:PaydayInfo(playerID, response, listItem, inputText[])
{
	// Nothing to do here
}