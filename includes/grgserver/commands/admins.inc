ACMD:addhouse(playerid, params[])
{
	new name[256];
	new Float:price;
	if (IsAdmin(playerid, ADMINLEVEL_SERVERADMIN))
	{
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
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
}

ACMD:showinterior(playerid, params[])
{
	ShowDialog(playerid, DIALOG_SHOWINTERIOR, 0);
	return COMMAND_OK;
}

ACMD:addpickup(playerid, params[])
{
	if (IsAdmin(playerid, ADMINLEVEL_SERVERADMIN))
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
		new id = AddPickup(type, posX, posY, posZ, true);
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
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
}

ACMD:controlnpc(playerid, params[])
{
	if (IsAdmin(playerid, ADMINLEVEL_SERVERADMIN))
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
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
}

ACMD:gmx(playerid, params[])
{
	if (IsAdmin(playerid, ADMINLEVEL_SERVERADMIN))
	{
		SendClientMessage(playerid, COLOR_INFO, "Gamemode neugestartet");
		SendRconCommand("gmx");
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
}

ACMD:goto(playerid, params[])
{
	if (IsAdmin(playerid, ADMINLEVEL_SERVERADMIN))
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
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
}

ACMD:gotobsn(playerid, params[])
{
	return AdminTeleport(playerid, 1204.7445, -881.0291, 43.0703, 0.0, 0, 0, ADMINLEVEL_SERVERADMIN);
}

ACMD:gotols(playerid, params[])
{
	return AdminTeleport(playerid, 1529.6, -1691.2, 13.3, 0.0, 0, 0, ADMINLEVEL_SERVERADMIN);
}

ACMD:gotolv(playerid, params[])
{
	return AdminTeleport(playerid, 1699.2, 1435.1, 10.7, 0.0, 0, 0, ADMINLEVEL_SERVERADMIN);
}

ACMD:gotosf(playerid, params[])
{
	return AdminTeleport(playerid, -1417.0, -295.8, 14.1, 0.0, 0, 0, ADMINLEVEL_SERVERADMIN);
}

ACMD:jetpack(playerid, params[])
{
	if (IsAdmin(playerid, ADMINLEVEL_SERVERADMIN))
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
		SendClientMessage(playerid, COLOR_INFO, "Viel Spaß mit deinem neuen JetPack!");
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
}

ACMD:kick(playerid, params[])
{
	new targetPlayerID;
	new reason[256];
	new string[256];
	if (IsAdmin(playerid, ADMINLEVEL_SERVERADMIN))
	{
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
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
}

ACMD:makeadmin(playerid, params[])
{
	new targetPlayerID;
	new level;
	if (IsAdmin(playerid, ADMINLEVEL_SERVERADMIN))
	{
		if (sscanf(params, "ud", targetPlayerID, level))
		{
			CmdUsageMsg(playerid, "makeadmin", "Spielername", "level (1-1337)");
			return COMMAND_USAGE;
		}
		if (IsPlayerConnected(targetPlayerID))
		{
			if (level >= 1 && level <= 1337)
			{
				new string[256];
				new adminPlayerName[MAX_PLAYER_NAME];
				new targetPlayerName[MAX_PLAYER_NAME];
				GetPlayerName(playerid, adminPlayerName, sizeof(adminPlayerName));
				GetPlayerName(targetPlayerID, targetPlayerName, sizeof(targetPlayerName));
				SetPVarInt(targetPlayerID, "AdminLevel", level);
				format(string, sizeof(string), "Du hast Admin Level %d von %s bekommen!", level, adminPlayerName);
				SendClientMessage(targetPlayerID, COLOR_INFO, string);
				format(string, sizeof(string), "Du hast Admin Level %d an %s gegeben!", level, targetPlayerName);
				SendClientMessage(playerid, COLOR_INFO, string);
				printf("%s got admin level %d by %s", targetPlayerName, level, adminPlayerName);
				return COMMAND_OK;
			}
			else
			{
				SendClientMessage(playerid, COLOR_ERROR, "Level muss zwischen 1 und 1337 sein!");
				return COMMAND_ERROR;
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_ERROR, "Spieler nicht gefunden!");
			return COMMAND_ERROR;
		}
	}
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
}

ACMD:money(playerid, params[])
{
	if (IsAdmin(playerid, ADMINLEVEL_SERVERADMIN))
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
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
}

ACMD:rc(playerid, params[])
{
	if (IsAdmin(playerid, ADMINLEVEL_SERVERADMIN))
	{
		printf("%s sent a RCON command: %s", GetPlayerNameEx(playerid), params);
		SendRconCommand(params);
		SendClientMessage(playerid, COLOR_INFO, "Der Befehl wurde ausgeführt");
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
}

ACMD:recnpc(playerid, params[])
{
	if (IsAdmin(playerid, ADMINLEVEL_SERVERADMIN))
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
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
}

ACMD:saveveh(playerid, params[])
{
	if (!IsAdmin(playerid, ADMINLEVEL_SERVERADMIN))
	{
		return COMMAND_ACCESS_DENIED;
	}
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
			format(query, sizeof(query), "INSERT INTO `savedvehicles` (`PosX`, `PosY`, `PosZ`, `Angle`, `Interior`, `ModelID`, `Price`, `CurrentFuel`) VALUES('%f', '%f', '%f', '%f', '%d', '%d', '%d', '%f')", posX, posY, posZ, angle, GetPlayerInterior(playerid), modelID, price, vehicleModels[modelID - 400][vehicleModels_maxFuel]);
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

ACMD:stoprec(playerid, params[])
{
	if (IsAdmin(playerid, ADMINLEVEL_SERVERADMIN))
	{
		StopRecordingPlayerData(playerid);
		SendClientMessage(playerid, COLOR_INFO, "Aufnahme gestoppt");
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
}

ACMD:veh(playerid, params[])
{
	if (!IsAdmin(playerid, ADMINLEVEL_SERVERADMIN))
	{
		return COMMAND_ACCESS_DENIED;
	}
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
			vehicles[vehicleID][vehicles_currentFuel] = vehicleModels[GetVehicleModel(vehicleID) - 400][vehicleModels_maxFuel];
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