ShowDialog:Bank_PIN(playerID)
{
	CreateDialog(playerID, "Bank_PIN", DIALOG_STYLE_INPUT, LanguageString(playerID, 579), LanguageString(playerID, 578), "OK", LanguageString(playerID, 165));
}

DialogResponse:Bank_PIN(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (!strlen(inputText))
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 19);
			ShowDialog:Bank_PIN(playerID);
		}
		else
		{
			MySQLQuery("INSERT INTO `bankaccounts` (`accountPIN`) VALUES('%s')", MD5(inputText));
			SendClientMessageEx(playerID, COLOR_INFO, 580);
		}
	}
}