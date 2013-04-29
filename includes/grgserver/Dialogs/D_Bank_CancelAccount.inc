ShowDialog:Bank_CancelAccount(playerID)
{
	CreateDialog(playerID, "Bank_CancelAccount", DIALOG_STYLE_MSGBOX, LanguageString(playerID, StringID:209("Cancel account")), LanguageString(playerID, StringID:214("Are you sure to cancel your account?")), LanguageString(playerID, StringID:166("Yes")), LanguageString(playerID, StringID:167("No")));
}

DialogResponse:Bank_CancelAccount(playerID, response, listItem, inputText[])
{
	if (response)
	{
		PVar:playerID[BANK_ID] = 0;
		LeaveProperty(playerID);
	}
	else
	{
		ShowDialog:Bank_HasAccount(playerID);
	}
}