ShowDialog:Stats(playerID)
{
	new string[1024];
	SavePlayer(playerID);
	Format:sqlQuery("SELECT `users`.`id`, `users`.`username`, UNIX_TIMESTAMP(`users`.`birthDate`) AS `birthDate`, `users`.`location`, `users`.`mobilePhoneNumber`, `users`.`bankAccountId`, `users`.`jobId`, `users`.`onlineTime`, `users`.`registerTime`, `users`.`loginTime`, `bankaccounts`.`money` AS `bankMoney`, `banks`.`name` AS `bank`, `jobs`.`name` AS `jobName` FROM `users`");
	MySQLQuery("%s LEFT JOIN (`bankaccounts`, `banks`, `jobs`) ON (`users`.`bankAccountId` = `bankaccounts`.`id` AND `bankaccounts`.`bankId` = `banks`.`id` AND `jobs`.`id` = `users`.`jobId`) WHERE `users`.`id` = '%d'", sqlQuery, PVar:playerID[USERID]);
	mysql_store_result();
	Format:string("ID: %s", GetMySQLField("id"));
	Format:string("%s\nName: %s", string, GetMySQLField("username"));
	Format:string("%s\n%s: %d %s", string, LanguageString(playerID, StringID:226("Age")), CalculateAge(strval(GetMySQLField("birthDate"))), LanguageString(playerID, StringID:307("Years")));
	Format:string("%s\n%s: %s", string, LanguageString(playerID, StringID:227("Home location")), GetMySQLField("location"));
	Format:string("%s\n%s: %s", string, LanguageString(playerID, StringID:228("Mobile phone number")), GetMySQLField("mobilePhoneNumber"));
	if (strval(GetMySQLField("bankAccountId")))
	{
		Format:string("%s\nBank: %s", string, GetMySQLField("bank"));
		Format:string("%s\n%s (Bank): %s", string, LanguageString(playerID, StringID:229("Credit")), FormatMoney(floatstr(GetMySQLField("bankMoney"))));
	}
	Format:string("%s\n%s: $%s", string, LanguageString(playerID, StringID:229("Credit")), FormatMoney(PVar:playerID[MONEY]));
	if (strval(GetMySQLField("jobId")))
	{
		Format:string("%s\n%s: %s", string, LanguageString(playerID, StringID:230("Occupation")), GetMySQLField("jobName"));
	}
	Format:string("%s\n%s: %s", string, LanguageString(playerID, StringID:231("Online time")), FormatTime(strval(GetMySQLField("onlineTime"))));
	Format:string("%s\n%s: %s", string, LanguageString(playerID, StringID:232("Registered since")), FormatDate(GetMySQLField("registerTime")));
	Format:string("%s\n%s: %s", string, LanguageString(playerID, StringID:233("Last login")), FormatDate(GetMySQLField("loginTime")));
	mysql_free_result();
	CreateDialog(playerID, "Stats", DIALOG_STYLE_MSGBOX, LanguageString(playerID, StringID:234("Personal data")), string, LanguageString(playerID, StringID:506("Close")), "");
}

DialogResponse:Stats(playerID, response, listItem, inputText[])
{
	// Nothing to do here
}