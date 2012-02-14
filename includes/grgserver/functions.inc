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
	if (IsPlayerConnected(playerID) && !IsPlayerNPC(playerID) && GetPVarInt(playerID, "UserID"))
	{
		printf("Saving player %s", GetPlayerNameEx(playerID));
		SavePlayerValue(playerID, "Level");
		SavePlayerValue(playerID, "AdminLevel");
		SavePlayerValue(playerID, "Money");
		SavePlayerValue(playerID, "Skin");
		new query[256];
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		GetPlayerPos(playerID, posX, posY, posZ);
		format(query, sizeof(query), "UPDATE `users` SET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f' WHERE `UserID` = '%d'", posX, posY, posZ, GetPVarInt(playerID, "UserID"));
		mysql_query(query);
	}
}

stock LoadPlayer(playerID)
{
	LoadPlayerValue(playerID, "Level", PLAYER_VARTYPE_INT);
	LoadPlayerValue(playerID, "AdminLevel", PLAYER_VARTYPE_INT);
	LoadPlayerValue(playerID, "Money", PLAYER_VARTYPE_FLOAT);
	LoadPlayerValue(playerID, "Skin", PLAYER_VARTYPE_INT);
	SetPlayerPos(playerID, floatstr(GetUserDBValue(playerID, "PosX")), floatstr(GetUserDBValue(playerID, "PosY")), floatstr(GetUserDBValue(playerID, "PosZ")));
	SetPlayerMoney(playerID, GetPVarFloat(playerID, "Money"));
	SetPlayerSkin(playerID, GetPVarInt(playerID, "Skin"));
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

stock IsValidSkin(skinID)
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

stock SaveVehicle(vehicleID, interior)
{
	if (vehicles[vehicleID][vehicles_saveID])
	{
		printf("Saving vehicle %d", vehicleID);
		new query[512];
		new Float:posX; 
		new Float:posY;
		new Float:posZ;
		GetVehiclePos(vehicleID, posX, posY, posZ);
		format(query, sizeof(query), "UPDATE `savedvehicles` SET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Interior` = '%d', `Color1` = '%d', `Color2` = '%d', `PaintjobID` = '%d', `CurrentFuel` = '%f' WHERE `ID` = '%d'", posX, posY, posZ, interior, vehicles[vehicleID][vehicles_color1], vehicles[vehicleID][vehicles_color2], vehicles[vehicleID][vehicles_paintjobID], vehicles[vehicleID][vehicles_currentFuel], vehicles[vehicleID][vehicles_saveID]);
		mysql_query(query);
		format(query, sizeof(query), "UPDATE `savedvehicles` SET `Component_Spoiler` = '%d', `Component_Hood` = '%d', `Component_Roof` = '%d', `Component_Sideskirt` = '%d' WHERE `ID` = '%d'", GetVehicleComponentInSlot(vehicleID, CARMODTYPE_SPOILER), GetVehicleComponentInSlot(vehicleID, CARMODTYPE_HOOD), GetVehicleComponentInSlot(vehicleID, CARMODTYPE_ROOF), GetVehicleComponentInSlot(vehicleID, CARMODTYPE_SIDESKIRT), vehicles[vehicleID][vehicles_saveID]);
		mysql_query(query);
		format(query, sizeof(query), "UPDATE `savedvehicles` SET `Component_Lamps` = '%d', `Component_Nitro` = '%d', `Component_Exhaust` = '%d', `Component_Wheels` = '%d' WHERE `ID` = '%d'", GetVehicleComponentInSlot(vehicleID, CARMODTYPE_LAMPS), GetVehicleComponentInSlot(vehicleID, CARMODTYPE_NITRO), GetVehicleComponentInSlot(vehicleID, CARMODTYPE_EXHAUST), GetVehicleComponentInSlot(vehicleID, CARMODTYPE_WHEELS), vehicles[vehicleID][vehicles_saveID]);
		mysql_query(query);
		format(query, sizeof(query), "UPDATE `savedvehicles` SET `Component_Stereo` = '%d', `Component_Hydraulics` = '%d', `Component_FrontBumper` = '%d', `Component_RearBumper` = '%d' WHERE `ID` = '%d'", GetVehicleComponentInSlot(vehicleID, CARMODTYPE_STEREO), GetVehicleComponentInSlot(vehicleID, CARMODTYPE_HYDRAULICS), GetVehicleComponentInSlot(vehicleID, CARMODTYPE_FRONT_BUMPER), GetVehicleComponentInSlot(vehicleID, CARMODTYPE_REAR_BUMPER), vehicles[vehicleID][vehicles_saveID]);
		mysql_query(query);
		format(query, sizeof(query), "UPDATE `savedvehicles` SET `Component_VentRight` = '%d', `Component_VentLeft` = '%d' WHERE `ID` = '%d'", GetVehicleComponentInSlot(vehicleID, CARMODTYPE_VENT_RIGHT), GetVehicleComponentInSlot(vehicleID, CARMODTYPE_VENT_LEFT), vehicles[vehicleID][vehicles_saveID]);
		mysql_query(query);
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
	if (!strcmp(type, "HOUSE", true))
	{
		pickupTypeID = PICKUPTYPE_HOUSE;
		modelID = PICKUP_HOUSEAVAILABLE;
		spawnType = 23;
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
