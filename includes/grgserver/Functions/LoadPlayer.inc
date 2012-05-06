LoadPlayer(playerID)
{
	MySQLQuery("SELECT * FROM `users` WHERE `ID` = '%d'", PVar:playerID[USERID]);
	mysql_store_result();
	new Float:bankMoney = floatstr(GetMySQLField("BankMoney"));
	new Float:cashMoney = floatstr(GetMySQLField("Money"));
	PVar:playerID[CHATMODE] = strval(GetMySQLField("ChatMode"));
	PVar:playerID[CURRENTPROPERTYID] = strval(GetMySQLField("CurrentPropertyID"));
	PVar:playerID[DEATHS] = strval(GetMySQLField("Deaths"));
	PVar:playerID[GODMODE] = strval(GetMySQLField("GodMode"));
	PVar:playerID[JOBID] = strval(GetMySQLField("JobID"));
	PVar:playerID[LANGUAGE] = strval(GetMySQLField("Language"));
	PVar:playerID[LASTNEWSID] = strval(GetMySQLField("LastNewsID"));
	PVar:playerID[LASTPAYDAY] = strval(GetMySQLField("LastPayDay"));
	PVar:playerID[ONLINESINCE] = gettime();
	PVar:playerID[ONLINETIME] = strval(GetMySQLField("OnlineTime"));
	PVar:playerID[SKIN] = strval(GetMySQLField("Skin"));
	PVar:playerID[SHOWCLOCK] = strval(GetMySQLField("ShowClock"));
	SetPlayerHealth(playerID, floatstr(GetMySQLField("Health")));
	SetPlayerSkin(playerID, PVar:playerID[SKIN]);
	mysql_free_result();
	SetPlayerMoney(playerID, MONEY_BANK, bankMoney);
	SetPlayerMoney(playerID, MONEY_CASH, cashMoney);
	MySQLQuery("SELECT * FROM `permissions` WHERE `UserID` = '%d'", PVar:playerID[USERID]);
	mysql_store_result();
	if (strval(GetMySQLField("UserID")))
	{
		LoadPlayerPermissions(playerID);
	}
	mysql_free_result();
}