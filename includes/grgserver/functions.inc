stock getPlayerName(playerid)
{
	new playerName[MAX_PLAYER_NAME];
	GetPlayerName(playerid, playerName, sizeof(playerName));
	return playerName;
}

stock getPlayerID(playerName[])
{
	for (new playerID; playerID < MAX_PLAYERS; playerID++)
	{
		if (IsPlayerConnected(playerID))
		{
			if (!strcmp(getPlayerName(playerID), playerName, true))
			{
				return playerID;
			}
		}
	}
	return INVALID_PLAYERID;
}

stock val2str(value)
{
	new string[256];
	format(string, sizeof(string), "%d", value);
	printf("val2str(%d): %s", value, string);
	return string;
}

stock fetchMySQLRow()
{
	new Line[1024];
	return mysql_fetch_row(Line);
}

stock getMySQLField(field[])
{
	new value[256];
	mysql_fetch_field(field, value);
	return value;
}

stock mySQLEscapeString(string[])
{
	new escapedString[256];
	mysql_real_escape_string(string, escapedString);
	return escapedString;
}

stock getMySQLValue(table[], field[], checkColumn[], checkValue[])
{
	new query[256];
	new string[256];
	format(query, sizeof(query), "SELECT `%s` FROM `%s` WHERE `%s` = '%s'", mySQLEscapeString(field), mySQLEscapeString(table), mySQLEscapeString(checkColumn), mySQLEscapeString(checkValue));
	mysql_query(query);
	mysql_store_result();
	format(string, sizeof(string), "%s", getMySQLField(field));
	mysql_free_result();
	return string;
}

stock setMySQLValue(table[], field[], value[], checkColumn[], checkValue[])
{
	new query[1024];
	printf("setMySQLValue(%s, %s, %s, %s, %s)", table, field, value, checkColumn, checkValue);
	format(query, sizeof(query), "UPDATE `%s` SET `%s` = '%s' WHERE `%s` = '%s'", mySQLEscapeString(table), mySQLEscapeString(field), mySQLEscapeString(value), mySQLEscapeString(checkColumn), mySQLEscapeString(checkValue));
	printf("SetMySQLValue: %s", query);
	mysql_query(query);
}

stock savePlayerValue(playerid, fieldName[])
{
	printf("SavePlayerValue(%d, %s)", playerid, fieldName);
	new value[256];
	switch (GetPVarType(playerid, fieldName))
	{
		case PLAYER_VARTYPE_INT:
			format(value, sizeof(value), "%d", GetPVarInt(playerid, fieldName));
		case PLAYER_VARTYPE_STRING:
			GetPVarString(playerid, fieldName, value, sizeof(value));
		case PLAYER_VARTYPE_FLOAT:
			format(value, sizeof(value), "%f", GetPVarFloat(playerid, fieldName));
		default:
			format(value, sizeof(value), "");
	}
	printf("Value: %s", value);
	setMySQLValue("users", fieldName, value, "UserID", val2str(GetPVarInt(playerid, "UserID")));
}

stock loadPlayerValue(playerid, fieldName[], pVarType)
{
	new value[256];
	format(value, sizeof(value), "%s", getMySQLValue("users", fieldName, "UserID", val2str(GetPVarInt(playerid, "UserID"))));
	switch (pVarType)
	{
		case PLAYER_VARTYPE_INT:
			SetPVarInt(playerid, fieldName, strval(value));
		case PLAYER_VARTYPE_STRING:
			SetPVarString(playerid, fieldName, value);
		case PLAYER_VARTYPE_FLOAT:
			SetPVarFloat(playerid, fieldName, floatstr(value));// TODO: Convert string value to float
	}
}

stock savePlayer(playerid)
{
	savePlayerValue(playerid, "Level");
	savePlayerValue(playerid, "AdminLevel");
}

stock loadPlayer(playerid)
{
	loadPlayerValue(playerid, "Level", PLAYER_VARTYPE_INT);
	loadPlayerValue(playerid, "AdminLevel", PLAYER_VARTYPE_INT);
}

stock setPlayerMoney(playerID, amount)
{
	ResetPlayerMoney(playerID);
	GivePlayerMoney(playeriID, amount);
}

stock isAdmin(playerID, adminLevel)
{
	return GetPVarInt(playerID, "AdminLevel") >= adminLevel;
}

stock teleportTo(playerID, Float:posX, Float:posY, Float:posZ, Float:angle, interior, virtualWorld)
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

stock adminTeleport(playerID, Float:posX, Float:posY, Float:posZ, Float:angle, interior, virtualWorld, adminLevel)
{
	if (isAdmin(playerID, adminLevel))
	{
		if (teleportTo(playerID, posX, posY, posZ, angle, interior, virtualWorld))
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

stock startNPCPlayback(npcPlayerID, recordingName[], recordingType, autoRepeat)
{
	new string[256];
	format(string, sizeof(string), "%s %d %d", recordingName, recordingType, autoRepeat);
	SendClientMessage(npcPlayerID, COLOR_NPCCOMMAND, string);
}

stock sendNPCCommand(npcPlayerID, command[])
{
	SendClientMessage(npcPlayerID, COLOR_NPCCOMMAND, command);
}

stock writeChatToDatabase(playerid, text[])
{
	new query[512];
	format(query, sizeof(query), "INSERT INTO `chatlog` (`UserID`, `Time`, `Text`) VALUES('%d', NOW(), '%s')", GetPVarInt(playerid, "UserID"), mySQLEscapeString(text));
	mysql_query(query);
}

stock CmdUsageMsg(playerid, command[], ...)
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
	SendClientMessage(playerid, COLOR_USAGE, string);
}