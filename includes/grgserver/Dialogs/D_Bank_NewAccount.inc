ShowDialog:Bank_NewAccount(playerID)
{
	CreateDialog(playerID, "Bank_NewAccount", DIALOG_STYLE_MSGBOX, LanguageString(playerID, 210), LanguageString(playerID, 211), LanguageString(playerID, 166), LanguageString(playerID, 167));
}

DialogResponse:Bank_NewAccount(playerID, response, listItem, inputText[])
{
	if (response)
	{
		MySQLQuery("SELECT `id` FROM `bankaccounts` WHERE '%d'");
		new bankAccountID = mysql_insert_id();
		new bankID = strval(GetMySQLValue("bankbranches", "bankId", "propertyId", val2str(PVar:playerID[CURRENTPROPERTYID])));
		MySQLQuery("UPDATE `users` SET `bankId` = '%d' WHERE `id` = '%d'", bankID, PVar:playerID[USERID]);
		MySQLQuery("UPDATE `users` SET `bankAccountId` = '%d' WHERE `id` = '%d'", bankAccountID, PVar:playerID[USERID]);
		SendClientMessageEx(playerID, COLOR_INFO, 216, GetMySQLValue("banks", "name", "id", val2str(bankID)));
		ShowDialog:Bank_PIN(playerID);
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