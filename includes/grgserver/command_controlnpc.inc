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
		FormatNew:string[100]("Befehl gesendet: %s", command);
		SendClientMessage(playerid, COLOR_INFO, string);
		SendNPCCommand(GetPlayerID(targetPlayerName), command);
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
}