CMD:about(playerid, params[])
{
	SendClientMessage(playerid, COLOR_INFO, "Created by Aerox_Tobi (aerox@grgserver.de) and Programie (programie@selfcoders.com)");
	return COMMAND_OK;
}

CMD:makeadmin(playerid, params[])
{
	new playerName[MAX_PLAYER_NAME];
	new level;
	if (GetPVarInt(playerid, "AdminLevel") >= ADMINLEVEL_SERVERADMIN)
	{
		if (!sscanf(params, "sd", playerName, level))
		{
			CmdUsageMsg(playerid, "makeadmin", "Spielername", "level (1-1337)");
		}
		new targetPlayerID = getPlayerByName(playerName);
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

CMD:gotobsn(playerid, params[])
{
	if (GetPVarInt(playerid, "AdminLevel") >= ADMINLEVEL_SERVERADMIN)
	{
		if (teleportTo(playerid, 1204.7445, -881.0291, 43.0703, 0.0, 0))
		{
			return COMMAND_TELEPORTED;
		}
		else
		{
			SendClientMessage(playerid, COLOR_ERROR, "Beim Teleportieren ist ein Fehler aufgetreten! Bitte erneut versuchen.");
			return COMMAND_ERROR;
		}
	}
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
}

CMD:gotols(playerid, params[])
{
	if (GetPVarInt(playerid, "AdminLevel") >= ADMINLEVEL_SERVERADMIN)
	{
		if (teleportTo(playerid, 1529.6, -1691.2, 13.3, 0.0, 0))
		{
			return COMMAND_TELEPORTED;
		}
		else
		{
			SendClientMessage(playerid, COLOR_ERROR, "Beim Teleportieren ist ein Fehler aufgetreten! Bitte erneut versuchen.");
			return COMMAND_ERROR;
		}
	}
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
}

CMD:gotolv(playerid, params[])
{
	if (GetPVarInt(playerid, "AdminLevel") >= ADMINLEVEL_SERVERADMIN)
	{
		if (teleportTo(playerid, 1699.2, 1435.1, 10.7, 0.0, 0))
		{
			return COMMAND_TELEPORTED;
		}
		else
		{
			SendClientMessage(playerid, COLOR_ERROR, "Beim Teleportieren ist ein Fehler aufgetreten! Bitte erneut versuchen.");
			return COMMAND_ERROR;
		}
	}
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
}

CMD:gotosf(playerid, params[])
{
	if (GetPVarInt(playerid, "AdminLevel") >= ADMINLEVEL_SERVERADMIN)
	{
		if (teleportTo(playerid, -1417.0, -295.8, 14.1, 0.0, 0))
		{
			return COMMAND_TELEPORTED;
		}
		else
		{
			SendClientMessage(playerid, COLOR_ERROR, "Beim Teleportieren ist ein Fehler aufgetreten! Bitte erneut versuchen.");
			return COMMAND_ERROR;
		}
	}
	else
	{
		return COMMAND_ACCESS_DENIED;
	}
}

CMD:veh(playerid, params[])
{
	if(GetPVarInt(playerid, "AdminLevel") >= ADMINLEVEL_SERVERADMIN)
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
			// TODO: Get ModelID by name
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