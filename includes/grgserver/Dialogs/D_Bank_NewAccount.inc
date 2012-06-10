ShowDialog:Bank_NewAccount(playerID)
{
	CreateDialog(playerID, "Bank_NewAccount", DIALOG_STYLE_MSGBOX, LanguageString(playerID, 210), LanguageString(playerID, 211), LanguageString(playerID, 166), LanguageString(playerID, 167));
}

DialogResponse:Bank_NewAccount(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new bankID = strval(GetMySQLValue("bankbranches", "bankId", "propertyId", val2str(PVar:playerID[CURRENTPROPERTYID])));
		MySQLQuery("UPDATE `users` SET `bankId` = '%d' WHERE `id` = '%d'", bankID, PVar:playerID[USERID]);
		SendClientMessageEx(playerID, COLOR_INFO, 216, GetMySQLValue("banks", "name", "id", val2str(bankID)));
		ShowDialog:Bank_HasAccount(playerID);
	}
	else
	{
		LeaveProperty(playerID);
	}
}