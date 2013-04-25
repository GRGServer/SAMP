ShowDialog:Bank_PINWRITE(playerID)
{
	CreateDialog(playerID, "Bank_PINWRITE", DIALOG_STYLE_INPUT, LanguageString(playerID, StringID:579("Your new PIN for your bank account is %d")), LanguageString(playerID, StringID:578("Your request has been sent")), "OK", LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:Bank_PINWRITE(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (!strlen(inputText))
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:19("You have to enter the amount!"));
			ShowDialog:Bank_PINWRITE(playerID);
		}
		else
		{
			MySQLQuery("SELECT `accountPIN` FROM `bankaccounts` WHERE '%s'", MD5(inputText));
			SendClientMessageEx(playerID, COLOR_INFO, StringID:580("Enter PIN"));
		}
	}
}