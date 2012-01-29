stock getPlayerName(playerID)
{
	new playerName[MAX_PLAYER_NAME];
	GetPlayerName(playerID, playerName, sizeof(playerName));
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

stock str_replace(search[], replace[], source[])
{
	new newnick[256];
	new newlen;
	for (new i; i < strlen(source); i++)
	{
		if (strlen(search) > 1 && i != (strlen(source) - 1))
		{
			new matched = 1;
			new start = i;
			for (new s=0; s < strlen(search) && matched == 1; s++)
			{
				if (source[i] != search[s] && s == 0)
				{
					newnick[newlen] = source[i];
					matched = 0;
				} else
				{
					if (source[i] == search[s])
					{
						i++;
					} else
					{
						matched = 0;
					}
				}
			}
			if (matched == 0)
			{
				for (start=start; start <= i; start++)
				{
					newnick[newlen] = source[start];
					newlen++;
				}
			} else
			{
				for (new r; r < strlen(replace); r++)
				{
					newnick[newlen] = replace[r];
					newlen++;
				}
				i = (start + (strlen(search) - 1));
			}
		} else
		{
			if (strlen(search) == 1 && source[i] == search[0])
			{
				for (new r; r < strlen(replace); r++)
				{
					newnick[newlen] = replace[r];
					newlen++;
				}
			} else
			{
				newnick[newlen] = source[i];
				newlen++;
			}
		}
	}
	newnick[newlen] = EOS;
	return newnick;
}

stock val2str(value)
{
	new string[256];
	format(string, sizeof(string), "%d", value);
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

stock getMySQLValue(table[], field[], checkColumn[], checkValue[], whereOperator[] = "=")
{
	new query[256];
	new string[256];
	format(query, sizeof(query), "SELECT `%s` FROM `%s` WHERE `%s` %s '%s'", mySQLEscapeString(field), mySQLEscapeString(table), mySQLEscapeString(checkColumn), whereOperator, mySQLEscapeString(checkValue));
	mysql_query(query);
	mysql_store_result();
	format(string, sizeof(string), "%s", getMySQLField(field));
	mysql_free_result();
	return string;
}

stock setMySQLValue(table[], field[], value[], checkColumn[], checkValue[])
{
	new query[1024];
	format(query, sizeof(query), "UPDATE `%s` SET `%s` = '%s' WHERE `%s` = '%s'", mySQLEscapeString(table), mySQLEscapeString(field), mySQLEscapeString(value), mySQLEscapeString(checkColumn), mySQLEscapeString(checkValue));
	mysql_query(query);
}

stock savePlayerValue(playerID, fieldName[])
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
	setUserDBValue(playerID, fieldName, value);
}

stock loadPlayerValue(playerID, fieldName[], pVarType)
{
	switch (pVarType)
	{
		case PLAYER_VARTYPE_INT:
			SetPVarInt(playerID, fieldName, strval(getUserDBValue(playerID, fieldName)));
		case PLAYER_VARTYPE_STRING:
			SetPVarString(playerID, fieldName, getUserDBValue(playerID, fieldName));
		case PLAYER_VARTYPE_FLOAT:
			SetPVarFloat(playerID, fieldName, floatstr(getUserDBValue(playerID, fieldName)));
	}
}

stock savePlayer(playerID)
{
	savePlayerValue(playerID, "Level");
	savePlayerValue(playerID, "AdminLevel");
	setUserDBValue(playerID, "Money", val2str(GetPlayerMoney(playerID)));
}

stock loadPlayer(playerID)
{
	loadPlayerValue(playerID, "Level", PLAYER_VARTYPE_INT);
	loadPlayerValue(playerID, "AdminLevel", PLAYER_VARTYPE_INT);
	setPlayerMoney(playerID, strval(getUserDBValue(playerID, "Money")));
}

stock setPlayerMoney(playerID, amount)
{
	ResetPlayerMoney(playerID);
	GivePlayerMoney(playerID, amount);
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

stock addNPCRecorderPlayback(playerID, recordingName[], recordingType)
{
	new npcPlayerName[MAX_PLAYER_NAME];
	format(npcPlayerName, sizeof(npcPlayerName), "%s_NPC1", getPlayerName(playerID));
	new npcPlayerID = getPlayerID(npcPlayerName);
	if (npcPlayerID == INVALID_PLAYERID)
	{
		new string[256];
		format(string, sizeof(string), "Der NPC '%s' ist nicht verbunden! Verwende /controlnpc %s connect und versuche es erneut.", npcPlayerName, npcPlayerName);
		SendClientMessage(playerID, COLOR_ERROR, string);
	}
	else
	{
		if (recordingType == PLAYER_RECORDING_TYPE_DRIVER)
		{
			new modelID = strval(getMySQLValue("npcs", "VehicleModelID", "Recording", recordingName));
			if (modelID)
			{
				PutPlayerInVehicle(npcPlayerID, CreateVehicle(modelID, 0.0, 0.0, 0.0, 0.0, random(126), random(126), 1), 0);
			}
		}
		SetPVarInt(npcPlayerID, "RecordNPCForPlayer", playerID);
		startNPCPlayback(npcPlayerID, recordingName, recordingType, false);
		return true;
	}
	return false;
}

stock writeChatToDatabase(playerID, text[])
{
	new query[512];
	format(query, sizeof(query), "INSERT INTO `chatlog` (`UserID`, `Time`, `Text`) VALUES('%d', NOW(), '%s')", GetPVarInt(playerID, "UserID"), mySQLEscapeString(text));
	mysql_query(query);
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
		getStringArg(index, value);
		format(string, sizeof(string), "%s %s", string, value);
	}
	SendClientMessage(playerID, COLOR_USAGE, string);
}