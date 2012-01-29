CMD:about(playerid, params[])
{
	SendClientMessage(playerid, COLOR_INFO, "Created by Aerox_Tobi (aerox@grgserver.de) and Programie (programie@selfcoders.com)");
	return COMMAND_OK;
}

CMD:controlnpc(playerid, params[])
{
	if (isAdmin(playerid, ADMINLEVEL_SERVERADMIN))
	{
		new playerName[MAX_PLAYER_NAME];
		new command[256];
		new recordingName[256];
		new playbackType[256];
		new autoRepeat;
		if (sscanf(params, "ssssd", playerName, command, recordingName, playbackType, autoRepeat))
		{
			if (sscanf(params, "ss", playerName, command))
			{
				CmdUsageMsg(playerid, "controlnpc", "playerName", "command(start|stop|pause|resume)", "[recordingName]", "[playbackType]", "[autoRepeat]");
				SendClientMessage(playerid, COLOR_INFO, "Hinweis: recordingName, playbackType und autoRepeat wird nur für den Befehl 'start' benötigt.");
				return COMMAND_OK;
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
				startNPCPlayback(getPlayerID(playerName), recordingName, type, autoRepeat);
				return COMMAND_OK;
			}
		}
		else
		{
			sendNPCCommand(getPlayerID(playerName), command);
			return COMMAND_OK;
		}
	}
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
	return COMMAND_ERROR;
}

CMD:goto(playerid, params[])
{
	if (isAdmin(playerid, ADMINLEVEL_SERVERADMIN))
	{
		new playerID;
		new playerName[MAX_PLAYER_NAME];
		if(sscanf(params,"d",playerID))
		{
			if(sscanf(params, "s",playerName))
			{
				CmdUsageMsg(playerid,"goto","PlayerID/Name");
				return COMMAND_OK;
			}
			else
			{
				playerID = getPlayerID(playerName);
			}
		}
		if (playerID != INVALID_PLAYERID && IsPlayerConnected(playerID))
		{
			new Float:posX;
			new Float:posY;
			new Float:posZ;
			new Float:angle;
			GetPlayerPos(playerID, posX, posY, posZ);
			GetPlayerFacingAngle(playerID, angle);
			if (teleportTo(playerid, posX, posY + 2, posZ, angle, GetPlayerInterior(playerID), GetPlayerVirtualWorld(playerID)))
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

CMD:gotobsn(playerid, params[])
{
	return adminTeleport(playerid, 1204.7445, -881.0291, 43.0703, 0.0, 0, 0, ADMINLEVEL_SERVERADMIN);
}

CMD:gotols(playerid, params[])
{
	return adminTeleport(playerid, 1529.6, -1691.2, 13.3, 0.0, 0, 0, ADMINLEVEL_SERVERADMIN);
}

CMD:gotolv(playerid, params[])
{
	return adminTeleport(playerid, 1699.2, 1435.1, 10.7, 0.0, 0, 0, ADMINLEVEL_SERVERADMIN);
}

CMD:gotosf(playerid, params[])
{
	return adminTeleport(playerid, -1417.0, -295.8, 14.1, 0.0, 0, 0, ADMINLEVEL_SERVERADMIN);
}

CMD:makeadmin(playerid, params[])
{
	new playerName[MAX_PLAYER_NAME];
	new level;
	if (isAdmin(playerid, ADMINLEVEL_SERVERADMIN))
	{
		if (!sscanf(params, "sd", playerName, level))
		{
			CmdUsageMsg(playerid, "makeadmin", "Spielername", "level (1-1337)");
		}
		new targetPlayerID = getPlayerID(playerName);
		if (targetPlayerID == INVALID_PLAYERID)
		{
			SendClientMessage(playerid, COLOR_ERROR, "Spieler nicht gefunden!");
		}
		else
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
			}
			else
			{
				SendClientMessage(playerid, COLOR_ERROR, "Level muss zwischen 1 und 1337 sein!");
			}
		}
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
}

CMD:printpvar(playerid, params[])
{
	new string[256];
	new name[256];
	if (!sscanf(playerid, "s", name))
	{
		GetPVarString(playerid, name, string, sizeof(string));
		format(string, sizeof(string), "Inhalt der Player Variable '%s': %s", name, string);
		SendClientMessage(playerid, COLOR_INFO, string);
	}
	else
	{
		CmdUsageMsg(playerid, "printpvar", "Variable");
	}
	return COMMAND_OK;
}

CMD:rc(playerid, params[])
{
	if (isAdmin(playerid, ADMINLEVEL_SERVERADMIN))
	{
		printf("%s sent a RCON command: %s", getPlayerName(playerid), params);
		SendRconCommand(params);
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
}

CMD:veh(playerid, params[])
{
	if(GetPVarInt(playerid, "AdminLevel") < ADMINLEVEL_SERVERADMIN)
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
					return COMMAND_OK;
				}
			}
			modelID = strval(getMySQLValue("vehicles", "ModelID", "Name", vehicleName));
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
			LinkVehicleToInterior(vehicleID, GetPlayerInterior(playerid));
			SetVehicleVirtualWorld(vehicleID, GetPlayerVirtualWorld(playerid));
			PutPlayerInVehicle(playerid, vehicleID, 0);
			printf("%s spawned a vehicle (ModelID: %d)", getPlayerName(playerid), modelID);
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