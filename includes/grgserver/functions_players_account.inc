IsLoggedIn(playerID)
{
	return (IsPlayerConnected(playerID) && !IsPlayerNPC(playerID) && GetPVar:playerID[USERID]);
}

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

SavePlayer(playerID)
{
	if (IsLoggedIn(playerID))
	{
		SetUserDBValue(playerID, "Money", Float2Str(GetPVar:playerID[MONEY]));
		SetUserDBValue(playerID, "Skin", val2str(GetPVar:playerID[SKIN]));
		SetUserDBValue(playerID, "CurrentBuildingID", val2str(GetPVar:playerID[CURRENTBUILDINGID]));
		SetUserDBValue(playerID, "JobID", val2str(GetPVar:playerID[JOBID]));
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		new Float:angle;
		GetPlayerPos(playerID, posX, posY, posZ);
		GetPlayerFacingAngle(playerID, angle);
		MySQLQuery("UPDATE `users` SET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Angle` = '%f', `Interior` = '%d' WHERE `UserID` = '%d'", posX, posY, posZ, angle, GetPlayerInterior(playerID), GetPVar:playerID[USERID]);
	}
}