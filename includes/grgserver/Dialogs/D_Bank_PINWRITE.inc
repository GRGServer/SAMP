ShowDialog:Bank_PINWRITE(playerID)
{
	CreateDialog(playerID, "Bank_PINWRITE", DIALOG_STYLE_INPUT, LanguageString(playerID, 579), LanguageString(playerID, 578), "OK", LanguageString(playerID, 165));
}

DialogResponse:Bank_PINWRITE(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (!strlen(inputText))
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 19);
			ShowDialog:Bank_PINWRITE(playerID);
		}
		else
		{
			MySQLQuery("SELECT `accountPIN` FROM `bankaccounts` WHERE '%s'", MD5(inputText));
			SendClientMessageEx(playerID, COLOR_INFO, 580);
		}
	}
}