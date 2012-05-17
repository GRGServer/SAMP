ShowDialog:Bank_CancelAccount(playerID)
{
	ShowMsgBox(playerID, "Bank_CancelAccount", LanguageString(playerID, 209), LanguageString(playerID, 214), MSGBOXSTYLE_YESNO);
}

DialogResponse:Bank_CancelAccount(playerID, response, listItem, inputText[])
{
	if (response)
	{
		SetUserDBValue(playerID, "BankID", "0");
		LeaveProperty(playerID);
	}
	else
	{
		ShowDialog:Bank_HasAccount(playerID);
	}
}