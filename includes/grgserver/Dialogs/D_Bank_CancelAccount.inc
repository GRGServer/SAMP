ShowDialog:Bank_CancelAccount(playerID)
{
	CreateDialog(playerID, "Bank_CancelAccount", DIALOG_STYLE_MSGBOX, LanguageString(playerID, 209), LanguageString(playerID, 214), LanguageString(playerID, 166), LanguageString(playerID, 167));
}

DialogResponse:Bank_CancelAccount(playerID, response, listItem, inputText[])
{
	if (response)
	{
		MySQLQuery("UPDATE `users` SET `bankAccountId` = '0' WHERE `id` = '%d'", PVar:playerID[USERID]);
		LeaveProperty(playerID);
	}
	else
	{
		ShowDialog:Bank_HasAccount(playerID);
	}
}