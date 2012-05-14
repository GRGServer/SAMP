ShowDialog:BANK_NEWACCOUNT(playerID)
{
	ShowMsgBox(playerID, "BANK_NEWACCOUNT", LanguageString(playerID, 210), LanguageString(playerID, 211), MSGBOXSTYLE_YESNO);
}

DialogResponse:BANK_NEWACCOUNT(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new bankID = strval(GetMySQLValue("bankbranches", "BankID", "PropertyID", val2str(PVar:playerID[CURRENTPROPERTYID])));
		SetUserDBValue(playerID, "BankID", val2str(bankID));
		SendClientMessageEx(playerID, COLOR_INFO, 216, GetMySQLValue("banks", "Name", "ID", val2str(bankID)));
		ShowDialog:BANK_HASACCOUNT(playerID);
	}
	else
	{
		LeaveProperty(playerID);
	}
}