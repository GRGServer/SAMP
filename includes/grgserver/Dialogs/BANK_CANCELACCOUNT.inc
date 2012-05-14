ShowDialog:BANK_CANCELACCOUNT(playerID)
{
	ShowMsgBox(playerID, "BANK_CANCELACCOUNT", LanguageString(playerID, 209), LanguageString(playerID, 214), MSGBOXSTYLE_YESNO);
}

DialogResponse:BANK_CANCELACCOUNT(playerID, response, listItem, inputText[])
{
	if (response)
	{
		SetUserDBValue(playerID, "BankID", "0");
		LeaveProperty(playerID);
	}
	else
	{
		ShowDialog:BANK_HASACCOUNT(playerID);
	}
}