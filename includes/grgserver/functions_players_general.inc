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

GivePlayerMoneyEx(playerID, Float:amount)
{
	SetPVar:playerID[MONEY](floatadd(GetPVar:playerID[MONEY], amount));
	ResetPlayerMoney(playerID);
	GivePlayerMoney(playerID, floatround(GetPVar:playerID[MONEY], floatround_tozero) * 100);
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
	new CurrentBuildingID = GetPVar:playerID[CURRENTBUILDINGID];
	if (CurrentBuildingID)
	{
		MySQLQuery("SELECT `PosX`, `PosY`, `PosZ` FROM `pickups` WHERE `ID` = '%d'", strval(GetMySQLValue("buildings", "PickupID", "ID", val2str(CurrentBuildingID))));
		mysql_store_result();
		SetPlayerPos(playerID, floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")));
		SetPlayerInterior(playerID, 0);
		SetPlayerVirtualWorld(playerID, 0);
		SetPVar:playerID[CURRENTBUILDINGID](0);
		mysql_free_result();
		return true;
	}
	return false;
}

ResetPlayerVariables(playerID)
{
	Count(playerVariable, sizeof(playerVariables[]))
	{
		playerVariables[playerID][enum_playerVariable:playerVariable] = 0;
	}
	SetPVar:playerID[RECORDNPCFORPLAYER](INVALID_PLAYER_ID);
	SetPVar:playerID[SHOWINTERIOR_OLDINTERIOR](-1);
}

SetPlayerMoney(playerID, Float:amount)
{
	SetPVar:playerID[MONEY](amount);
	ResetPlayerMoney(playerID);
	GivePlayerMoney(playerID, floatround(amount, floatround_tozero) * 100);
}