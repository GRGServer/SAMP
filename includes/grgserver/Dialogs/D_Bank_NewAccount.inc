ShowDialog:Bank_NewAccount(playerID)
{
	CreateDialog(playerID, "Bank_NewAccount", DIALOG_STYLE_MSGBOX, LanguageString(playerID, 210), LanguageString(playerID, 211), LanguageString(playerID, 166), LanguageString(playerID, 167));
}

DialogResponse:Bank_NewAccount(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new bankName[100];
		new pin = RandomEx(BANK_PIN_MIN, BANK_PIN_MAX);
		MySQLQuery("SELECT `id`, `name` FROM `banks` LEFT JOIN `bankbranches` ON `bankbranches`.`bankId` = `banks`.`id` WHERE `bankbranches`.`propertyId` = '%d'", PVar:playerID[CURRENTPROPERTYID]);
		mysql_store_result();
		strcat(bankName, GetMySQLField("name"));
		new bankId = strval(GetMySQLField("id"));
		mysql_free_result();
		MySQLQuery("INSERT INTO `bankaccounts` (`bankId`, `pin`) VALUES('%d', '%d')", bankId, pin);
		new bankAccountId = mysql_insert_id();
		MySQLQuery("UPDATE `users` SET `bankAccountId` = '%d' WHERE `id` = '%d'", bankAccountId, PVar:playerID[USERID]);
		SendClientMessageEx(playerID, COLOR_INFO, 216, bankName);
		SendClientMessageEx(playerID, COLOR_INFO, 579, pin);
		if (PVar:playerID[INTUTORIAL])
		{
			TogglePlayerControllable(playerID, false);
			StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_TUTORIAL_BANK_LEAVE_BLACK);
		}
		else
		{
			ShowDialog:Bank_HasAccount(playerID);
		}
	}
	else
	{
		LeaveProperty(playerID);
	}
}