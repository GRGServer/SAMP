IsLoggedIn(playerID)
{
	return (IsPlayerConnected(playerID) && !IsPlayerNPC(playerID) && GetPVarInt(playerID, "UserID"));
}

LoadPlayer(playerID)
{
	LoadPlayerValue(playerID, "Level", PLAYER_VARTYPE_INT);
	LoadPlayerValue(playerID, "AdminLevel", PLAYER_VARTYPE_INT);
	LoadPlayerValue(playerID, "Money", PLAYER_VARTYPE_FLOAT);
	LoadPlayerValue(playerID, "Skin", PLAYER_VARTYPE_INT);
	LoadPlayerValue(playerID, "CurrentBuildingID", PLAYER_VARTYPE_INT);
	SetPlayerMoney(playerID, GetPVarFloat(playerID, "Money"));
	SetPlayerSkin(playerID, GetPVarInt(playerID, "Skin"));
	new query[256];
	format(query, sizeof(query), "SELECT * FROM `permissions` WHERE `UserID` = '%d'", GetPVarInt(playerID, "UserID"));
	mysql_query(query);
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
		SavePlayerValue(playerID, "Level");
		SavePlayerValue(playerID, "AdminLevel");
		SavePlayerValue(playerID, "Money");
		SavePlayerValue(playerID, "Skin");
		SavePlayerValue(playerID, "CurrentBuildingID");
		new query[256];
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		new Float:angle;
		GetPlayerPos(playerID, posX, posY, posZ);
		GetPlayerFacingAngle(playerID, angle);
		format(query, sizeof(query), "UPDATE `users` SET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Angle` = '%f', `Interior` = '%d' WHERE `UserID` = '%d'", posX, posY, posZ, angle, GetPlayerInterior(playerID), GetPVarInt(playerID, "UserID"));
		mysql_query(query);
	}
}

SavePlayerValue(playerID, fieldName[])
{
	new value[256];
	switch (GetPVarType(playerID, fieldName))
	{
		case PLAYER_VARTYPE_INT:
			format(value, sizeof(value), "%d", GetPVarInt(playerID, fieldName));
		case PLAYER_VARTYPE_STRING:
			GetPVarString(playerID, fieldName, value, sizeof(value));
		case PLAYER_VARTYPE_FLOAT:
			format(value, sizeof(value), "%f", GetPVarFloat(playerID, fieldName));
		default:
			format(value, sizeof(value), "");
	}
	SetUserDBValue(playerID, fieldName, value);
}