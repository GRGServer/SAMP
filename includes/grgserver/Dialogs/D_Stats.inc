ShowDialog:Stats(playerID)
{
	new string[1024];
	SavePlayer(playerID);
	Format:sqlQuery("SELECT `users`.`id`, `users`.`username`, UNIX_TIMESTAMP(`users`.`birthDate`) AS `birthDate`, `users`.`location`, `users`.`mobilePhoneNumber`, `users`.`bankAccountId`, `users`.`jobId`, `users`.`onlineTime`, `users`.`registerTime`, `users`.`loginTime`, `bankaccounts`.`money` AS `bankMoney`, `banks`.`name` AS `bank`, `jobs`.`name` AS `jobName` FROM `users`");
	MySQLQuery("%s LEFT JOIN (`bankaccounts`, `banks`, `jobs`) ON (`users`.`bankAccountId` = `bankaccounts`.`id` AND `bankaccounts`.`bankId` = `banks`.`id` AND `jobs`.`id` = `users`.`jobId`) WHERE `users`.`id` = '%d'", sqlQuery, PVar:playerID[USERID]);
	mysql_store_result();
	Format:string("ID: %s", GetMySQLField("id"));
	Format:string("%s\nName: %s", string, GetMySQLField("username"));
	Format:string("%s\n%s: %d %s", string, LanguageString(playerID, "226"), CalculateAge(strval(GetMySQLField("birthDate"))), LanguageString(playerID, "307"));
	Format:string("%s\n%s: %s", string, LanguageString(playerID, "227"), GetMySQLField("location"));
	Format:string("%s\n%s: %s", string, LanguageString(playerID, "228"), GetMySQLField("mobilePhoneNumber"));
	if (strval(GetMySQLField("bankAccountId")))
	{
		Format:string("%s\nBank: %s", string, GetMySQLField("bank"));
		Format:string("%s\n%s (Bank): %s", string, LanguageString(playerID, "229"), FormatMoney(floatstr(GetMySQLField("bankMoney"))));
	}
	Format:string("%s\n%s: $%s", string, LanguageString(playerID, "229"), FormatMoney(PVar:playerID[MONEY]));
	if (strval(GetMySQLField("jobId")))
	{
		Format:string("%s\n%s: %s", string, LanguageString(playerID, "230"), GetMySQLField("jobName"));
	}
	Format:string("%s\n%s: %s", string, LanguageString(playerID, "231"), FormatTime(strval(GetMySQLField("onlineTime"))));
	Format:string("%s\n%s: %s", string, LanguageString(playerID, "232"), FormatDate(GetMySQLField("registerTime")));
	Format:string("%s\n%s: %s", string, LanguageString(playerID, "233"), FormatDate(GetMySQLField("loginTime")));
	mysql_free_result();
	CreateDialog(playerID, "Stats", DIALOG_STYLE_MSGBOX, LanguageString(playerID, "234"), string, LanguageString(playerID, "506"), "");
}

DialogResponse:Stats(playerID, response, listItem, inputText[])
{
	// Nothing to do here
}