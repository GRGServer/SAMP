ShowDialog:Stats(playerID)
{
	new string[1024];
	SavePlayer(playerID);
	Format:sqlQuery("SELECT `users`.`ID`, `users`.`Username`, UNIX_TIMESTAMP(`users`.`BirthDate`) AS `BirthDate`, `users`.`Location`, `users`.`MobilePhoneNumber`, `users`.`BankID`, `users`.`BankMoney`, `users`.`JobID`, `users`.`OnlineTime`, `users`.`RegisterTime`, `users`.`LoginTime`, `banks`.`Name` AS `Bank`, `jobs`.`Name` AS `JobName` FROM `users`");
	MySQLQuery("%s LEFT JOIN (`banks`, `jobs`) ON (`banks`.`ID` = `users`.`BankID` AND `jobs`.`ID` = `users`.`JobID`) WHERE `users`.`ID` = '%d'", sqlQuery, PVar:playerID[USERID]);
	mysql_store_result();
	Format:string("ID: %s", GetMySQLField("ID"));
	Format:string("%s\nName: %s", string, GetMySQLField("Username"));
	Format:string("%s\n%s: %d %s", string, LanguageString(playerID, 226), CalculateAge(strval(GetMySQLField("BirthDate"))), LanguageString(playerID, 307));
	Format:string("%s\n%s: %s", string, LanguageString(playerID, 227), GetMySQLField("Location"));
	Format:string("%s\n%s: %s", string, LanguageString(playerID, 228), GetMySQLField("MobilePhoneNumber"));
	if (strval(GetMySQLField("BankID")))
	{
		Format:string("%s\nBank: %s", string, GetMySQLField("Bank"));
		Format:string("%s\n%s (Bank): %s", string, LanguageString(playerID, 229), FormatMoney(floatstr(GetMySQLField("BankMoney"))));
	}
	Format:string("%s\n%s: $%s", string, LanguageString(playerID, 229), FormatMoney(PVar:playerID[MONEY]));
	if (strval(GetMySQLField("JobID")))
	{
		Format:string("%s\n%s: %s", string, LanguageString(playerID, 230), GetMySQLField("JobName"));
	}
	Format:string("%s\n%s: %s", string, LanguageString(playerID, 231), FormatTime(strval(GetMySQLField("OnlineTime"))));
	Format:string("%s\n%s: %s", string, LanguageString(playerID, 232), FormatDate(GetMySQLField("RegisterTime")));
	Format:string("%s\n%s: %s", string, LanguageString(playerID, 233), FormatDate(GetMySQLField("LoginTime")));
	mysql_free_result();
	ShowMsgBox(playerID, "Stats", LanguageString(playerID, 234), string);
}

DialogResponse:Stats(playerID, response, listItem, inputText[])
{
	// Nothing to do here
}