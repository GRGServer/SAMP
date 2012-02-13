stock GetPlayerNameEx(playerID)
{
	new playerName[MAX_PLAYER_NAME];
	GetPlayerName(playerID, playerName, sizeof(playerName));
	return playerName;
}

stock GetPlayerID(playerName[])
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

stock FetchMySQLRow()
{
	new Line[1024];
	return mysql_fetch_row(Line);
}

stock GetMySQLField(field[])
{
	new value[256];
	mysql_fetch_field(field, value);
	return value;
}

stock MySQLEscapeString(string[])
{
	new escapedString[256];
	mysql_real_escape_string(string, escapedString);
	return escapedString;
}

stock GetMySQLValue(table[], field[], checkColumn[], checkValue[], whereOperator[] = "=")
{
	new query[256];
	new string[256];
	format(query, sizeof(query), "SELECT `%s` FROM `%s` WHERE `%s` %s '%s'", MySQLEscapeString(field), MySQLEscapeString(table), MySQLEscapeString(checkColumn), whereOperator, MySQLEscapeString(checkValue));
	mysql_query(query);
	mysql_store_result();
	format(string, sizeof(string), "%s", GetMySQLField(field));
	mysql_free_result();
	return string;
}

stock SetMySQLValue(table[], field[], value[], checkColumn[], checkValue[])
{
	new query[1024];
	format(query, sizeof(query), "UPDATE `%s` SET `%s` = '%s' WHERE `%s` = '%s'", MySQLEscapeString(table), MySQLEscapeString(field), MySQLEscapeString(value), MySQLEscapeString(checkColumn), MySQLEscapeString(checkValue));
	mysql_query(query);
}

stock SavePlayerValue(playerID, fieldName[])
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

stock LoadPlayerValue(playerID, fieldName[], pVarType)
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

stock SavePlayer(playerID)
{
	SavePlayerValue(playerID, "Level");
	SavePlayerValue(playerID, "AdminLevel");
	SavePlayerValue(playerID, "Money");
	new query[256];
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	GetPlayerPos(playerID, posX, posY, posZ);
	format(query, sizeof(query), "UPDATE `users` SET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f' WHERE `UserID` = '%d'", posX, posY, posZ, GetPVarInt(playerID, "UserID"));
	mysql_query(query);
}

stock LoadPlayer(playerID)
{
	LoadPlayerValue(playerID, "Level", PLAYER_VARTYPE_INT);
	LoadPlayerValue(playerID, "AdminLevel", PLAYER_VARTYPE_INT);
	LoadPlayerValue(playerID, "Money", PLAYER_VARTYPE_FLOAT);
	SetPlayerPos(playerID, floatstr(GetUserDBValue(playerID, "PosX")), floatstr(GetUserDBValue(playerID, "PosY")), floatstr(GetUserDBValue(playerID, "PosZ")));
	SetPlayerMoney(playerID, GetPVarFloat(playerID, "Money"));
}

stock SetPlayerMoney(playerID, Float:amount)
{
	SetPVarFloat(playerID, "Money", amount);
	ResetPlayerMoney(playerID);
	GivePlayerMoney(playerID, floatround(amount, floatround_tozero) * 100);
}

stock GivePlayerMoneyEx(playerID, Float:amount)
{
	SetPVarFloat(playerID, "Money", floatadd(GetPVarFloat(playerID, "Money"), amount));
	ResetPlayerMoney(playerID);
	GivePlayerMoney(playerID, floatround(GetPVarFloat(playerID, "Money"), floatround_tozero) * 100);
}

stock SendClientMessageToAllExcept(exceptPlayerID, color, message[])
{
	for (new playerID; playerID < MAX_PLAYERS; playerID++)
	{
		if (playerID != exceptPlayerID && IsPlayerConnected(playerID))
		{
			SendClientMessage(playerID, color, message);
		}
	}
}

stock IsAdmin(playerID, adminLevel)
{
	return GetPVarInt(playerID, "AdminLevel") >= adminLevel;
}

stock TeleportTo(playerID, Float:posX, Float:posY, Float:posZ, Float:angle, interior, virtualWorld)
{
	switch (GetPlayerState(playerID))
	{
		case PLAYER_STATE_ONFOOT:
		{
			SetPlayerPos(playerID, posX, posY, posZ);
			SetPlayerFacingAngle(playerID, angle);
			SetPlayerInterior(playerID, interior);
			SetPlayerVirtualWorld(playerID, virtualWorld);
			return true;
		}
		case PLAYER_STATE_DRIVER, PLAYER_STATE_PASSENGER:
		{
			new vehicleID = GetPlayerVehicleID(playerID);
			SetVehiclePos(vehicleID, posX, posY, posZ);
			LinkVehicleToInterior(vehicleID, interior);
			SetVehicleVirtualWorld(vehicleID, virtualWorld);
			return true;
		}
	}
	return false;
}

stock AdminTeleport(playerID, Float:posX, Float:posY, Float:posZ, Float:angle, interior, virtualWorld, adminLevel)
{
	if (IsAdmin(playerID, adminLevel))
	{
		if (TeleportTo(playerID, posX, posY, posZ, angle, interior, virtualWorld))
		{
			return COMMAND_TELEPORTED;
		}
		else
		{
			SendClientMessage(playerID, COLOR_ERROR, "Beim Teleportieren ist ein Fehler aufgetreten! Bitte versuche es erneut.");
			return COMMAND_ERROR;
		}
	}
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
}

stock StartNPCPlayback(npcPlayerID, recordingName[], recordingType, autoRepeat)
{
	new string[256];
	format(string, sizeof(string), "%s %d %d", recordingName, recordingType, autoRepeat);
	SendClientMessage(npcPlayerID, COLOR_NPCCOMMAND, string);
}

stock SendNPCCommand(npcPlayerID, command[])
{
	SendClientMessage(npcPlayerID, COLOR_NPCCOMMAND, command);
}

stock AddNPCRecorderPlayback(playerID, recordingName[], recordingType)
{
	new npcPlayerName[MAX_PLAYER_NAME];
	format(npcPlayerName, sizeof(npcPlayerName), "%s_NPC1", GetPlayerNameEx(playerID));
	new npcPlayerID = GetPlayerID(npcPlayerName);
	if (npcPlayerID == INVALID_PLAYER_ID)
	{
		new string[256];
		format(string, sizeof(string), "Der NPC '%s' ist nicht verbunden! Verwende /controlnpc %s connect und versuche es erneut.", npcPlayerName, npcPlayerName);
		SendClientMessage(playerID, COLOR_ERROR, string);
	}
	else
	{
		if (recordingType == PLAYER_RECORDING_TYPE_DRIVER)
		{
			new modelID = strval(GetMySQLValue("npcs", "VehicleModelID", "Recording", recordingName));
			if (modelID)
			{
				PutPlayerInVehicle(npcPlayerID, CreateVehicle(modelID, 0.0, 0.0, 0.0, 0.0, random(126), random(126), 1), 0);
			}
		}
		SetPVarInt(npcPlayerID, "RecordNPCForPlayer", playerID);
		StartNPCPlayback(npcPlayerID, recordingName, recordingType, false);
		return true;
	}
	return false;
}

stock WriteChatToDatabase(playerID, text[])
{
	new query[512];
	format(query, sizeof(query), "INSERT INTO `chatlog` (`UserID`, `Time`, `Text`) VALUES('%d', NOW(), '%s')", GetPVarInt(playerID, "UserID"), MySQLEscapeString(text));
	mysql_query(query);
}

stock GetVehicleEngineState(vehicleID)
{
	new engine;
	new lights;
	new alarm;
	new doors;
	new bonnet;
	new boot;
	new objective;
	GetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, bonnet, boot, objective);
	return engine;
}

stock SetVehicleEngineState(vehicleID, newState)
{
	new engine;
	new lights;
	new alarm;
	new doors;
	new bonnet;
	new boot;
	new objective;
	GetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, bonnet, boot, objective);
	if (engine != newState)
	{
		SetVehicleParamsEx(vehicleID, newState, lights, alarm, doors, bonnet, boot, objective);
	}
}

stock AddPickup(type[], Float:posX, Float:posY, Float:posZ, saveToDB)
{
	new pickupTypeID = -1;
	new modelID;
	new spawnType;
	new pickup;
	if (!strcmp(type, "BANK", true))
	{
		pickupTypeID = PICKUPTYPE_BANK;
		modelID = PICKUP_BANK;
		spawnType = 23;
	}
	if (!strcmp(type, "GASSTATION", true))
	{
		pickupTypeID = PICKUPTYPE_GASSTATION;
		modelID = PICKUP_GASSTATION;
		spawnType = 14;
	}
	if (pickupTypeID == -1)
	{
		return -1;
	}
	else
	{
		pickup = CreatePickup(modelID, spawnType, posX, posY, posZ);
		pickups[pickup][pickups_type] = pickupTypeID;
		if (saveToDB)
		{
			new query[256];
			format(query, sizeof(query), "INSERT INTO `pickups` (`PosX`, `PosY`, `PosZ`, `Type`) VALUES('%f', '%f', '%f', '%s')", posX, posY, posZ, type);
			mysql_query(query);
			return mysql_insert_id();
		}
		else
		{
			return -2;
		}
	}
}

stock UpdateGasPrice()
{
	gasPrice = float(150 + random(10)) / 100;
}

stock CmdUsageMsg(playerID, command[], ...)
{
	new string[256];
	new value[256];
	new parameters;
	parameters = numargs();
	format(string, sizeof(string), "Verwendung: /%s", command);
	for (new index = 2; index < parameters; index++)
	{
		GetStringArg(index, value);
		format(string, sizeof(string), "%s %s", string, value);
	}
	SendClientMessage(playerID, COLOR_USAGE, string);
}
