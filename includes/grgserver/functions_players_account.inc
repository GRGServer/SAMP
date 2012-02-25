IsLoggedIn(playerID)
{
	return (IsPlayerConnected(playerID) && !IsPlayerNPC(playerID) && GetUserID(playerID));
}

LoadPlayer(playerID)
{
	LoadPlayerValue(playerID, "Money", PLAYER_VARTYPE_FLOAT);
	LoadPlayerValue(playerID, "Skin", PLAYER_VARTYPE_INT);
	LoadPlayerValue(playerID, "CurrentBuildingID", PLAYER_VARTYPE_INT);
	SetPlayerMoney(playerID, GetPlayerMoneyEx(playerID));
	SetPlayerSkin(playerID, GetPVarInt(playerID, "Skin"));
	MySQLQuery("SELECT * FROM `permissions` WHERE `UserID` = '%d'", GetUserID(playerID));
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

LoadPlayerValue(playerID, fieldName[], pVarType)
{
	switch (pVarType)
	{
		case PLAYER_VARTYPE_INT:
			SetPVarInt(playerID, fieldName, strval(GetUserDBValue(playerID, fieldName)));
		case PLAYER_VARTYPE_STRING:
			SetPVarString(playerID, fieldName, GetUserDBValue(playerID, fieldName));
		case PLAYER_VARTYPE_FLOAT:
			SetPVarFloat(playerID, fieldName, floatstr(GetUserDBValue(playerID, fieldName)));
	}
}

SavePlayer(playerID)
{
	if (IsLoggedIn(playerID))
	{
		SavePlayerValue(playerID, "Money");
		SavePlayerValue(playerID, "Skin");
		SavePlayerValue(playerID, "CurrentBuildingID");
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		new Float:angle;
		GetPlayerPos(playerID, posX, posY, posZ);
		GetPlayerFacingAngle(playerID, angle);
		MySQLQuery("UPDATE `users` SET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Angle` = '%f', `Interior` = '%d' WHERE `UserID` = '%d'", posX, posY, posZ, angle, GetPlayerInterior(playerID), GetUserID(playerID));
	}
}

SavePlayerValue(playerID, fieldName[])
{
	new value[256];
	switch (GetPVarType(playerID, fieldName))
	{
		case PLAYER_VARTYPE_INT:
			Format:value("%d", GetPVarInt(playerID, fieldName));
		case PLAYER_VARTYPE_STRING:
			GetPVarString(playerID, fieldName, value, sizeof(value));
		case PLAYER_VARTYPE_FLOAT:
			Format:value("%f", GetPVarFloat(playerID, fieldName));
		default:
			Format:value("");
	}
	SetUserDBValue(playerID, fieldName, value);
}