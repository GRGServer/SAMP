LoadPlayer(playerID)
{
	SetPVar:playerID[MONEY](floatstr(GetUserDBValue(playerID, "Money")));
	SetPVar:playerID[SKIN](strval(GetUserDBValue(playerID, "Skin")));
	SetPVar:playerID[CURRENTBUILDINGID](strval(GetUserDBValue(playerID, "CurrentBuildingID")));
	SetPVar:playerID[JOBID](strval(GetUserDBValue(playerID, "JobID")));
	SetPlayerMoney(playerID, GetPVar:playerID[MONEY]);
	SetPlayerSkin(playerID, GetPVar:playerID[SKIN]);
	MySQLQuery("SELECT * FROM `permissions` WHERE `UserID` = '%d'", GetPVar:playerID[USERID]);
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