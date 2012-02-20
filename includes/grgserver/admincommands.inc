ACMD:addhouse[MAPPER](playerid, params[])
{
	new name[256];
	new Float:price;
	if (sscanf(params, "sf", name, price))
	{
		CmdUsageMsg(playerid, "addhouse", "Name", "Preis");
		return COMMAND_USAGE;
	}
	SetPVarString(playerid, "AddHouse_Name", name);
	SetPVarFloat(playerid, "AddHouse_Price", price);
	ShowDialog(playerid, DIALOG_ADDHOUSE, 0);
	return COMMAND_OK;
}

ACMD:addpickup[MAPPER](playerid, params[])
{
	new type[256];
	new string[256];
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	if (sscanf(params, "s", type))
	{
		CmdUsageMsg(playerid, "addpickup", "BANK/GASSTATION/HOUSE");
		return COMMAND_USAGE;
	}
	format(type, sizeof(type), "%s", strtoupper(type));
	GetPlayerPos(playerid, posX, posY, posZ);
	new id = AddPickup(-1, type, posX, posY, posZ, true);
	if (id > 0)
	{
		format(string, sizeof(string), "Das Pickup %s wurde unter der ID %d gespeichert", type, id);
		SendClientMessage(playerid, COLOR_INFO, string);
		return COMMAND_OK;
	}
	else
	{
		SendClientMessage(playerid, COLOR_ERROR, "Ungültiger Typ!");
		return COMMAND_ERROR;
	}
}

ACMD:checkpermissions[ADMIN](playerid, params[])
{
	new string[1024];
	for (new permission = 0; permission < sizeof(permissions[]); permission++)
	{
		if (permissions[playerid][enum_permission:permission])
		{
			if (strlen(string))
			{
				format(string, sizeof(string), "%s ", string);
			}
			format(string, sizeof(string), "%s%s", string, GetPermissionName(permission));
		}
	}
	format(string, sizeof(string), "Du hast die folgenden Rechte: %s", string);
	SendClientMessage(playerid, COLOR_INFO, string);
	return COMMAND_OK;
}

ACMD:controlnpc[NPCADMIN](playerid, params[])
{
	new command[256];
	new recordingName[256];
	new playbackType[256];
	new autoRepeat;
	new targetPlayerID;
	if (sscanf(params, "usssd", targetPlayerID, command, recordingName, playbackType, autoRepeat))
	{
		if (sscanf(params, "us", targetPlayerID, command))
		{
			CmdUsageMsg(playerid, "controlnpc", "PlayerID/Name", "command(connect|start|stop|pause|resume)", "[recordingName]", "[playbackType]", "[autoRepeat]");
			SendClientMessage(playerid, COLOR_INFO, "Hinweis: recordingName, playbackType und autoRepeat wird nur für den Befehl 'start' benötigt.");
			return COMMAND_USAGE;
		}
	}
	if (!strcmp(command, "start", true))
	{
		new type;
		if (!strcmp(playbackType, "onfoot", true) || !strcmp(playbackType, "foot"))
		{
			type = PLAYER_RECORDING_TYPE_ONFOOT;
		}
		if (!strcmp(playbackType, "driver", true))
		{
			type = PLAYER_RECORDING_TYPE_DRIVER;
		}
		if (type)
		{
			SendClientMessage(playerid, COLOR_INFO, "Wiedergabe gestartet");
			StartNPCPlayback(targetPlayerID, recordingName, type, autoRepeat);
			return COMMAND_OK;
		}
		else
		{
			return COMMAND_ERROR;
		}
	}
	if (!strcmp(command, "connect", true))
	{
		SendClientMessage(playerid, COLOR_INFO, "NPC verbunden");
		ConnectNPC(GetPlayerNameEx(targetPlayerID), "npcplayer");
		return COMMAND_OK;
	}
	SendClientMessage(playerid, COLOR_INFO, "Befehl gesendet");
	SendNPCCommand(targetPlayerID, command);
	return COMMAND_OK;
}

ACMD:givepermission[SERVERADMIN](playerid, params[])
{
	new targetPlayerID;
	new permissionString[256];
	if (sscanf(params, "us", targetPlayerID, permissionString))
	{
		CmdUsageMsg(playerid, "givepermission", "Spielername", "Recht(Admin|Mapper|Moderator|NPCAdmin|ServerAdmin|Teleport)");
		return COMMAND_USAGE;
	}
	if (IsPlayerConnected(targetPlayerID))
	{
		new permissionsArray[30][30];
		new permission[30];
		explode(permissionString, permissionsArray, ',', sizeof(permissionsArray));
		for (new permissionIndex = 0; permissionIndex < sizeof(permissionsArray); permissionIndex++)
		{
			format(permission, sizeof(permission), permissionsArray[permissionIndex]);
			if (strcmp(permission, "UserID", true))
			{
				new newState = true;
				if (permission[0] == '-')
				{
					strdel(permission, 0, 1);
					newState = false;
				}
				new query[256];
				new string[256];
				new permissionID = GetPermissionByName(permission);
				if (permissions[playerid][enum_permission:permissionID] == newState)
				{
					if (newState)
					{
						format(string, sizeof(string), "%s hat bereits das Recht %s", GetPlayerNameEx(targetPlayerID), permission);
					}
					else
					{
						format(string, sizeof(string), "%s hatte das Recht %s noch nicht ud kann daher nicht entfernt werden", GetPlayerNameEx(targetPlayerID), permission);
					}
					SendClientMessage(playerid, COLOR_ERROR, string);
					return COMMAND_ERROR;
				}
				format(query, sizeof(query), "SELECT `UserID` FROM `permissions` WHERE `UserID` = '%d'", GetPVarInt(targetPlayerID, "UserID"));
				mysql_query(query);
				mysql_store_result();
				if (mysql_num_rows())
				{
					format(query, sizeof(query), "UPDATE `permissions` SET `%s` = '%d' WHERE `UserID` = '%d'", MySQLEscapeString(permission), newState, GetPVarInt(targetPlayerID, "UserID"));
				}
				else
				{
					format(query, sizeof(query), "INSERT INTO `permissions` (`UserID`, `%s`) VALUES('%d', '%d')", MySQLEscapeString(permission), GetPVarInt(targetPlayerID, "UserID"), newState);
				}
				mysql_free_result();
				mysql_query(query);
				permissions[targetPlayerID][enum_permission:permissionID] = newState;
				format(string, sizeof(string), "Du hast das Recht %s von %s bekommen!", permission, GetPlayerNameEx(playerid));
				SendClientMessage(targetPlayerID, COLOR_INFO, string);
				format(string, sizeof(string), "Du hast das Recht %s an %s gegeben!", permission, GetPlayerNameEx(targetPlayerID));
				SendClientMessage(playerid, COLOR_INFO, string);
				printf("%s got permission %s by %s", GetPlayerNameEx(targetPlayerID), permission, GetPlayerNameEx(playerid));
			}
		}
		return COMMAND_OK;
	}
	else
	{
		SendClientMessage(playerid, COLOR_ERROR, "Spieler nicht gefunden!");
		return COMMAND_ERROR;
	}
}

ACMD:gmx[SERVERADMIN](playerid, params[])
{
	SendClientMessage(playerid, COLOR_INFO, "Du hast den Gamemode neugestartet");
	new string[256];
	format(string, sizeof(string), "%s hat den Gamemode neugestartet");
	SendClientMessageToAllExcept(playerid, COLOR_INFO, string);
	SendRconCommand("gmx");
	return COMMAND_OK;
}

ACMD:goto[ADMIN](playerid, params[])
{
	new targetPlayerID;
	if (sscanf(params, "u", targetPlayerID))
	{
		CmdUsageMsg(playerid, "goto", "PlayerID/Name");
		return COMMAND_USAGE;
	}
	if (IsPlayerConnected(targetPlayerID))
	{
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		new Float:angle;
		GetPlayerPos(targetPlayerID, posX, posY, posZ);
		GetPlayerFacingAngle(targetPlayerID, angle);
		if (TeleportTo(playerid, posX, posY, posZ, angle, GetPlayerInterior(targetPlayerID), GetPlayerVirtualWorld(targetPlayerID)))
		{
			return COMMAND_TELEPORTED;
		}
		else
		{
			return COMMAND_ERROR;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_ERROR, "Spieler nicht gefunden!");
	}
	return COMMAND_OK;
}

ACMD:gotobsn[TELEPORT](playerid, params[])
{
	return Teleport(playerid, 1204.7445, -881.0291, 43.0703, 0.0, 0, 0);
}

ACMD:gotols[TELEPORT](playerid, params[])
{
	return Teleport(playerid, 1529.6, -1691.2, 13.3, 0.0, 0, 0);
}

ACMD:gotolv[TELEPORT](playerid, params[])
{
	return Teleport(playerid, 1699.2, 1435.1, 10.7, 0.0, 0, 0);
}

ACMD:gotosf[TELEPORT](playerid, params[])
{
	return Teleport(playerid, -1417.0, -295.8, 14.1, 0.0, 0, 0);
}

ACMD:jetpack[ADMIN](playerid, params[])
{
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
	SendClientMessage(playerid, COLOR_INFO, "Viel Spaß mit deinem neuen JetPack!");
	return COMMAND_OK;
}

ACMD:kick[MODERATOR](playerid, params[])
{
	new targetPlayerID;
	new reason[256];
	new string[256];
	if (sscanf(params, "us", targetPlayerID, reason))
	{
		CmdUsageMsg(playerid, "kick", "Spielername/ID", "Grund");
		return COMMAND_USAGE;
	}
	if (IsPlayerConnected(targetPlayerID))
	{
		Kick(targetPlayerID);
		format(string, sizeof(string), "%s wurde von %s gekickt, Grund: %s", GetPlayerNameEx(targetPlayerID), GetPlayerNameEx(playerid), reason);
		SendClientMessageToAll(COLOR_ERROR, string);
		printf("%s has been kicked by %s, Reason: %s", GetPlayerNameEx(targetPlayerID), GetPlayerNameEx(playerid), reason);
		return COMMAND_OK;
	}
	else
	{
		SendClientMessage(playerid, COLOR_ERROR, "Der Spieler wurde nicht gefunden!");
		return COMMAND_ERROR;
	}
}

ACMD:money[ADMIN](playerid, params[])
{
	new money;
	if (!sscanf(params, "f", money))
	{
		GivePlayerMoneyEx(playerid, money);
		return COMMAND_OK;
	}
	else
	{
		CmdUsageMsg(playerid, "money", "Wert");
		return COMMAND_USAGE;
	}
}

ACMD:rc[SERVERADMIN](playerid, params[])
{
	printf("%s sent a RCON command: %s", GetPlayerNameEx(playerid), params);
	SendRconCommand(params);
	SendClientMessage(playerid, COLOR_INFO, "Der Befehl wurde ausgeführt");
	return COMMAND_OK;
}

ACMD:recnpc[NPCADMIN](playerid, params[])
{
	new npcs;
	new recordingType;
	new recordingName[256];
	new playbackName1[256];
	new playbackName2[256];
	new playbackName3[256];
	new string[256];
	if (sscanf(params, "ssss", recordingName, playbackName1, playbackName2, playbackName3))
	{
		if (sscanf(params, "sss", recordingName, playbackName1, playbackName2))
		{
			if (sscanf(params, "ss", recordingName, playbackName1))
			{
				if (sscanf(params, "s", recordingName))
				{
					CmdUsageMsg(playerid, "recnpc", "recordingName", "[playbackName1]", "[playbackName2]", "[playbackName3]");
					return COMMAND_USAGE;
				}
			}
		}
	}
	if (IsPlayerInAnyVehicle(playerid))
	{
		recordingType = PLAYER_RECORDING_TYPE_DRIVER;
	}
	else
	{
		recordingType = PLAYER_RECORDING_TYPE_ONFOOT;
	}
	if (strlen(playbackName1))
	{
		if (!AddNPCRecorderPlayback(playerid, playbackName1, recordingType))
		{
			return COMMAND_ERROR;
		}
		npcs++;
	}
	if (strlen(playbackName2))
	{
		if (!AddNPCRecorderPlayback(playerid, playbackName2, recordingType))
		{
			return COMMAND_ERROR;
		}
		npcs++;
	}
	if (strlen(playbackName3))
	{
		if (!AddNPCRecorderPlayback(playerid, playbackName3, recordingType))
		{
			return COMMAND_ERROR;
		}
		npcs++;
	}
	StartRecordingPlayerData(playerid, recordingType, recordingName);
	format(string, sizeof(string), "Aufnahme '%s' mit %d weiteren NPCs gestartet", recordingName, npcs);
	SendClientMessage(playerid, COLOR_INFO, string);
	SendClientMessage(playerid, COLOR_INFO, "Verwende /stoprec zum stoppen.");
	return COMMAND_OK;
}

ACMD:saveveh[MAPPER](playerid, params[])
{
	new price;
	if (sscanf(params, "d", price))
	{
		CmdUsageMsg(playerid, "saveveh", "Preis");
		return COMMAND_USAGE;
	}
	if (price >= 0)
	{
		if (IsPlayerInAnyVehicle(playerid))
		{
			new string[256];
			new query[256];
			new Float:posX;
			new Float:posY;
			new Float:posZ;
			new Float:angle;
			new vehicleID = GetPlayerVehicleID(playerid);
			new modelID = GetVehicleModel(vehicleID);
			GetVehiclePos(vehicleID, posX, posY, posZ);
			GetVehicleZAngle(playerid, angle);
			format(query, sizeof(query), "INSERT INTO `savedvehicles` (`PosX`, `PosY`, `PosZ`, `Angle`, `Interior`, `ModelID`, `Price`, `CurrentFuel`) VALUES('%f', '%f', '%f', '%f', '%d', '%d', '%d', '%f')", posX, posY, posZ, angle, GetPlayerInterior(playerid), modelID, price, vehicleModels[modelID - 400][VEHICLEMODEL_MAXFUEL]);
			mysql_query(query);
			format(string, sizeof(string), "Fahrzeug wurde unter der ID %d gespeichert", mysql_insert_id());
			SendClientMessage(playerid, COLOR_INFO, string);
			return COMMAND_OK;
		}
		else
		{
			return COMMAND_NOT_IN_VEHICLE;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_ERROR, "Der Preis darf nicht negativ sein!");
	}
	return COMMAND_ERROR;
}

ACMD:setexit[MAPPER](playerid, params[])
{
	new buildingID;
	if (sscanf(params, "d", buildingID))
	{
		buildingID = GetPVarInt(playerid, "LastAddedHouse");
	}
	if (buildingID)
	{
		if (strval(GetMySQLValue("buildings", "ID", "ID", val2str(buildingID))))
		{
			new query[256];
			new Float:posX;
			new Float:posY;
			new Float:posZ;
			GetPlayerPos(playerid, posX, posY, posZ);
			format(query, sizeof(query), "UPDATE `buildings` SET `ExitPosX` = '%f', `ExitPosY` = '%f', `ExitPosZ` = '%f' WHERE `ID` = '%d'", posX, posY, posZ, buildingID);
			mysql_query(query);
			return COMMAND_OK;
		}
		else
		{
			SendClientMessage(playerid, COLOR_ERROR, "Ungültige ID!");
			return COMMAND_ERROR;
		}
	}
	else
	{
		CmdUsageMsg(playerid, "setexit", "[BuildingID]");
		return COMMAND_USAGE;
	}
}

ACMD:showinterior[ADMIN](playerid, params[])
{
	ShowDialog(playerid, DIALOG_SHOWINTERIOR, 0);
	return COMMAND_OK;
}

ACMD:stoprec[NPCADMIN](playerid, params[])
{
	StopRecordingPlayerData(playerid);
	SendClientMessage(playerid, COLOR_INFO, "Aufnahme gestoppt");
	return COMMAND_OK;
}

ACMD:veh[MAPPER](playerid, params[])
{
	new vehicleName[256];
	new modelID;
	new color1;
	new color2;
	if (sscanf(params, "ddd", modelID, color1, color2))
	{
		if (!sscanf(params, "d", modelID))
		{
			color1 = random(126);
			color2 = random(126);
		}
		else
		{
			if (sscanf(params, "sdd", vehicleName, color1, color2))
			{
				if (!sscanf(params, "s", vehicleName))
				{
					color1 = random(126);
					color2 = random(126);
				}
				else
				{
					CmdUsageMsg(playerid, "veh", "ModelID/Name", "[Color1]", "[Color2]");
					return COMMAND_USAGE;
				}
			}
			modelID = strval(GetMySQLValue("vehiclemodels", "ModelID", "Name", str_replace("*", "%%", vehicleName), "LIKE"));
		}
	}
	if (modelID >= 400 && modelID <= 611)
	{
		if (color1 >= 0 && color1 <= 126 && color2 >= 0 && color2 <= 126)
		{
			new Float:posX;
			new Float:posY;
			new Float:posZ;
			GetPlayerPos(playerid, posX, posY, posZ);
			new vehicleID = CreateVehicle(modelID, posX, posY, posZ, 0.0, color1, color2, -1);
			vehicles[vehicleID][VEHICLE_CURRENTFUEL] = vehicleModels[GetVehicleModel(vehicleID) - 400][VEHICLEMODEL_MAXFUEL];
			LinkVehicleToInterior(vehicleID, GetPlayerInterior(playerid));
			SetVehicleVirtualWorld(vehicleID, GetPlayerVirtualWorld(playerid));
			PutPlayerInVehicle(playerid, vehicleID, 0);
			printf("%s spawned a vehicle (ModelID: %d)", GetPlayerNameEx(playerid), modelID);
			SendClientMessage(playerid, COLOR_INFO, "Das Fahrzeug wurde gespawnt");
			return COMMAND_OK;
		}
		else
		{
			SendClientMessage(playerid, COLOR_ERROR, "Die Farbe muss zwischen 0 und 126 sein!");
		}
	}
	else
	{
		if (strlen(vehicleName))
		{
			SendClientMessage(playerid, COLOR_ERROR, "Das Fahrzeug wurde nicht gefunden!");
		}
		else
		{
			SendClientMessage(playerid, COLOR_ERROR, "Die ModelID muss zwischen 400 und 611 sein!");
		}
	}
	return COMMAND_ERROR;
}