LoadPlayer(playerID)
{
	PVar:playerID[BANKMONEY] = floatstr(GetUserDBValue(playerID, "BankMoney"));
	PVar:playerID[CREDITMONEY] = floatstr(GetUserDBValue(playerID, "CreditMoney"));
	PVar:playerID[MONEY] = floatstr(GetUserDBValue(playerID, "Money"));
	PVar:playerID[SKIN] = strval(GetUserDBValue(playerID, "Skin"));
	PVar:playerID[CURRENTBUILDINGID] = strval(GetUserDBValue(playerID, "CurrentBuildingID"));
	PVar:playerID[JOBID] = strval(GetUserDBValue(playerID, "JobID"));
	PVar:playerID[ONLINETIME] = strval(GetUserDBValue(playerID, "OnlineTime"));
	PVar:playerID[ONLINESINCE] = gettime();
	SetPlayerMoney(playerID, PVar:playerID[MONEY]);
	SetPlayerSkin(playerID, PVar:playerID[SKIN]);
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