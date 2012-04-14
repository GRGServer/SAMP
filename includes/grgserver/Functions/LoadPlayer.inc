LoadPlayer(playerID)
{
	MySQLQuery("SELECT * FROM `users` WHERE `ID` = '%d'", PVar:playerID[USERID]);
	mysql_store_result();
	SetPlayerMoney(playerID, MONEY_BANK, floatstr(GetMySQLField("BankMoney")));
	SetPlayerMoney(playerID, MONEY_CASH, floatstr(GetMySQLField("Money")));
	PVar:playerID[CURRENTBUILDINGID] = strval(GetMySQLField("CurrentBuildingID"));
	PVar:playerID[JOBID] = strval(GetMySQLField("JobID"));
	PVar:playerID[LANGUAGE] = strval(GetMySQLField("Language"));
	PVar:playerID[LASTNEWSID] = strval(GetMySQLField("LastNewsID"));
	PVar:playerID[LASTPAYDAY] = strval(GetMySQLField("LastPayDay"));
	PVar:playerID[ONLINESINCE] = gettime();
	PVar:playerID[ONLINETIME] = strval(GetMySQLField("OnlineTime"));
	PVar:playerID[SKIN] = strval(GetMySQLField("Skin"));
	SetPlayerHealth(playerID, floatstr(GetMySQLField("Health")));
	SetPlayerSkin(playerID, PVar:playerID[SKIN]);
	mysql_free_result();
	MySQLQuery("SELECT * FROM `permissions` WHERE `UserID` = '%d'", PVar:playerID[USERID]);
	mysql_store_result();
	if (strval(GetMySQLField("UserID")))
	{
		LoadPermission:ADMIN(playerID, "Admin");
		LoadPermission:MAPPER(playerID, "Mapper");
		LoadPermission:MODERATOR(playerID, "Moderator");
		LoadPermission:NPCADMIN(playerID, "NPCAdmin");
		LoadPermission:SERVERADMIN(playerID, "ServerAdmin");
		LoadPermission:TELEPORT(playerID, "Teleport");
	}
	mysql_free_result();
}