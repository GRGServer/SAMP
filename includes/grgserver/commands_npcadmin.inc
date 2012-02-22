PCMD:controlnpc[NPCADMIN](playerid, params[])
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
		ConnectNPC(GetPlayerNameEx(targetPlayerID), NPC_SCRIPTNAME);
		return COMMAND_OK;
	}
	SendClientMessage(playerid, COLOR_INFO, "Befehl gesendet");
	SendNPCCommand(targetPlayerID, command);
	return COMMAND_OK;
}

PCMD:recnpc[NPCADMIN](playerid, params[])
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

PCMD:stoprec[NPCADMIN](playerid, params[])
{
	StopRecordingPlayerData(playerid);
	SendClientMessage(playerid, COLOR_INFO, "Aufnahme gestoppt");
	return COMMAND_OK;
}