ShowDialog:Bank_NewAccount(playerID)
{
	ShowMsgBox(playerID, "Bank_NewAccount", LanguageString(playerID, 210), LanguageString(playerID, 211), MSGBOXSTYLE_YESNO);
}

DialogResponse:Bank_NewAccount(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new bankID = strval(GetMySQLValue("bankbranches", "BankID", "PropertyID", val2str(PVar:playerID[CURRENTPROPERTYID])));
		SetUserDBValue(playerID, "BankID", val2str(bankID));
		SendClientMessageEx(playerID, COLOR_INFO, 216, GetMySQLValue("banks", "Name", "ID", val2str(bankID)));
		ShowDialog:Bank_HasAccount(playerID);
	}
	else
	{
		LeaveProperty(playerID);
	}
}