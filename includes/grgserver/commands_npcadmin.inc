PCMD:addstaticnpc[NPCADMIN](playerid, params[], "NPC ohne Aufnahme an die aktuelle Position stellen")
{
	new playerName[MAX_PLAYER_NAME];
	if (sscanf(params, "s", playerName))
	{
		CmdUsageMsg(playerid, "addstaticnpc", "Playername");
		return COMMAND_USAGE;
	}
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:angle;
	GetPlayerPos(playerid, posX, posY, posZ);
	GetPlayerFacingAngle(playerid, angle);
	MySQLQuery("INSERT INTO `npcs` (`Name`, `SpawnPosX`, `SpawnPosY`, `SpawnPosZ`, `SpawnAngle`, `AutoConnect`) VALUES('%s', '%f', '%f', '%f', '%f', '1')", MySQLEscapeString(playerName), posX, posY, posZ, angle);
	new id = mysql_insert_id();
	if (id > 0)
	{
		Format:playerName("NPC_%s", playerName);
		ConnectNPC(playerName, NPC_SCRIPTNAME);
		FormatNew:string[70]("Der NPC wurde erfolgreich unter der ID %d gespeichert", id);
		SendClientMessage(playerid, COLOR_INFO, string);
		return COMMAND_OK;
	}
	else
	{
		SendClientMessage(playerid, COLOR_ERROR, "Während dem Speichern ist ein Fehler aufgetreten!");
	}
	return COMMAND_ERROR;
}

PCMD:controlnpc[NPCADMIN](playerid, params[], "NPCs steuern (z.B. Starten oder stoppen)")
{
	new command[256];
	new recordingName[256];
	new playbackType[256];
	new targetPlayerName[MAX_PLAYER_NAME];
	new autoRepeat;
	if (sscanf(params, "ssssd", targetPlayerName, command, recordingName, playbackType, autoRepeat))
	{
		if (sscanf(params, "ss", targetPlayerName, command))
		{
			CmdUsageMsg(playerid, "controlnpc", "Playername", "command(connect|start|stop|pause|resume)", "[recordingName]", "[playbackType]", "[autoRepeat]");
			SendClientMessage(playerid, COLOR_INFO, "Hinweis: recordingName, playbackType und autoRepeat wird nur für den Befehl 'start' benötigt.");
			return COMMAND_USAGE;
		}
	}
	Format:targetPlayerName("NPC_%s", targetPlayerName);
	if (!strcmp(command, "connect", true))
	{
		SendClientMessage(playerid, COLOR_INFO, "NPC verbunden");
		ConnectNPC(targetPlayerName, NPC_SCRIPTNAME);
		return COMMAND_OK;
	}
	if (GetPlayerID(targetPlayerName) != INVALID_PLAYER_ID)
	{
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
				StartNPCPlayback(GetPlayerID(targetPlayerName), recordingName, type, autoRepeat);
				return COMMAND_OK;
			}
			else
			{
				return COMMAND_ERROR;
			}
		}
		SendClientMessage(playerid, COLOR_INFO, "Befehl gesendet");
		SendNPCCommand(GetPlayerID(targetPlayerName), command);
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
}

PCMD:recnpc[NPCADMIN](playerid, params[], "Neue NPC Aufnahme erstellen")
{
	new npcs;
	new recordingType;
	new recordingName[256];
	new playbackName1[256];
	new playbackName2[256];
	new playbackName3[256];
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
	FormatNew:string[256]("Aufnahme '%s' mit %d weiteren NPCs gestartet", recordingName, npcs);
	SendClientMessage(playerid, COLOR_INFO, string);
	SendClientMessage(playerid, COLOR_INFO, "Verwende /stoprec zum stoppen.");
	return COMMAND_OK;
}

PCMD:stoprec[NPCADMIN](playerid, params[], "Aktuelle NPC Aufnahme beenden")
{
	StopRecordingPlayerData(playerid);
	SendClientMessage(playerid, COLOR_INFO, "Aufnahme gestoppt");
	return COMMAND_OK;
}