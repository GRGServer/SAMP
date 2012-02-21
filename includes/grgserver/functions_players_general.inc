GetPlayerID(playerName[])
{
	for (new playerID; playerID < MAX_PLAYERS; playerID++)
	{
		if (IsPlayerConnected(playerID))
		{
			if (!strcmp(GetPlayerNameEx(playerID), playerName, true))
			{
				return playerID;
			}
		}
	}
	return INVALID_PLAYER_ID;
}

GetPlayerNameEx(playerID)
{
	new playerName[MAX_PLAYER_NAME];
	GetPlayerName(playerID, playerName, sizeof(playerName));
	return playerName;
}

GetPVarStringEx(playerID, name[])
{
	new string[256];
	GetPVarString(playerID, name, string, sizeof(string));
	return string;
}

GivePlayerMoneyEx(playerID, Float:amount)
{
	SetPVarFloat(playerID, "Money", floatadd(GetPVarFloat(playerID, "Money"), amount));
	ResetPlayerMoney(playerID);
	GivePlayerMoney(playerID, floatround(GetPVarFloat(playerID, "Money"), floatround_tozero) * 100);
}

IsValidSkin(skinID)
{
	if (skinID >= 0 && skinID <= 298)
	{
		switch (skinID)
		{
			case 3, 4, 5, 6, 8, 42, 65, 74, 86, 119, 149, 208, 265, 266, 267, 268, 269, 270, 271, 272, 273, 289:
				return false;
		}
		return true;
	}
	return false;
}

LeaveBuilding(playerID)
{
	new CurrentBuildingID = GetPVarInt(playerID, "CurrentBuildingID");
	if (CurrentBuildingID)
	{
		new query[256];
		format(query, sizeof(query), "SELECT * FROM `buildings` WHERE `ID` = '%d'", val2str(CurrentBuildingID));
		printf("SQL: %s", query);
		mysql_query(query);
		mysql_store_result();
		SetPlayerPos(playerID, floatstr(GetMySQLField("ExitPosX")), floatstr(GetMySQLField("ExitPosY")), floatstr(GetMySQLField("ExitPosZ")));
		SetPlayerInterior(playerID, 0);
		SetPlayerVirtualWorld(playerID, 0);
		SetPVarInt(playerID, "CurrentBuildingID", 0);
		mysql_free_result();
		return true;
	}
	return false;
}

SetPlayerMoney(playerID, Float:amount)
{
	SetPVarFloat(playerID, "Money", amount);
	ResetPlayerMoney(playerID);
	GivePlayerMoney(playerID, floatround(amount, floatround_tozero) * 100);
}