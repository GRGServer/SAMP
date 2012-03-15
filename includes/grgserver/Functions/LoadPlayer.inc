LoadPlayer(playerID)
{
	MySQLQuery("SELECT * FROM `users` WHERE `UserID` = '%d'", PVar:playerID[USERID]);
	mysql_store_result();
	PVar:playerID[BANKMONEY] = floatstr(GetMySQLField("BankMoney"));
	PVar:playerID[CREDITMONEY] = floatstr(GetMySQLField("CreditMoney"));
	PVar:playerID[CURRENTBUILDINGID] = strval(GetMySQLField("CurrentBuildingID"));
	PVar:playerID[JOBID] = strval(GetMySQLField("JobID"));
	format(PVar:playerID[LANGUAGE], STRINGLENGTH_LANGUAGEKEY, GetMySQLField("Language"));
	PVar:playerID[LASTNEWSID] = strval(GetMySQLField("LastNewsID"));
	PVar:playerID[LASTPAYDAY] = strval(GetMySQLField("LastPayDay"));
	PVar:playerID[MONEY] = floatstr(GetMySQLField("Money"));
	PVar:playerID[ONLINESINCE] = gettime();
	PVar:playerID[ONLINETIME] = strval(GetMySQLField("OnlineTime"));
	PVar:playerID[SKIN] = strval(GetMySQLField("Skin"));
	SetPlayerHealth(playerID, floatstr(GetMySQLField("Health")));
	SetPlayerMoney(playerID, PVar:playerID[MONEY]);
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