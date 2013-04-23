ShowDialog:Bank_PIN(playerID)
{
	CreateDialog(playerID, "Bank_PIN", DIALOG_STYLE_INPUT, LanguageString(playerID, StringID:580("")), LanguageString(playerID, StringID:581("")), "OK", LanguageString(playerID, StringID:165("")));
}

DialogResponse:Bank_PIN(playerID, response, listItem, inputText[])
{
	if (!response)
	{
		LeaveProperty(playerID);
		return false;
	}
	new pin = strval(inputText);
	if (pin < BANK_PIN_MIN || pin > BANK_PIN_MAX)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:582(""), BANK_PIN_MIN, BANK_PIN_MAX);
		ShowDialog:Bank_PIN(playerID);
		return false;
	}
	MySQLQuery("SELECT `bankaccounts`.`id`, `bankaccounts`.`pin`, `bankaccounts`.`pinAttempts` FROM `bankaccounts` LEFT JOIN `users` ON `users`.`bankAccountId` = `bankaccounts`.`id` WHERE `users`.`id` = '%d'", PVar:playerID[USERID]);
	mysql_store_result();
	new id = strval(GetMySQLField("id"));
	new pinCorrect = (strval(GetMySQLField("pin")) == pin);
	new pinAttempts = strval(GetMySQLField("pinAttempts"));
	mysql_free_result();
	if (pinAttempts >= BANK_PIN_MAXATTEMPTS)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:585(""));
		LeaveProperty(playerID);
		return false;
	}
	if (pinCorrect)
	{
		MySQLQuery("UPDATE `bankaccounts` SET `pinAttempts` = '0' WHERE `id` = '%d'", id);
		ShowDialog:Bank_HasAccount(playerID);
		return true;
	}
	SendClientMessageEx(playerID, COLOR_ERROR, StringID:583(""));
	if (pinAttempts >= BANK_PIN_MAXATTEMPTS)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:585(""));
		LeaveProperty(playerID);
		return false;
	}
	pinAttempts++;
	MySQLQuery("UPDATE `bankaccounts` SET `pinAttempts` = '%d' WHERE `id` = '%d'", pinAttempts, id);
	if (pinAttempts >= BANK_PIN_MAXATTEMPTS)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:585(""));
		LeaveProperty(playerID);
		return false;
	}
	SendClientMessageEx(playerID, COLOR_ERROR, StringID:584(""), BANK_PIN_MAXATTEMPTS - pinAttempts);
	ShowDialog:Bank_PIN(playerID);
	return false;
}