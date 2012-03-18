PCMD:controlnpc[NPCADMIN](playerid, params[], 100)
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
			SendClientMessageEx(playerid, COLOR_INFO, 124);
			return COMMAND_USAGE;
		}
	}
	Format:targetPlayerName("NPC_%s", targetPlayerName);
	if (!strcmp(command, "connect", true))
	{
		SendClientMessageEx(playerid, COLOR_INFO, 125);
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
				SendClientMessageEx(playerid, COLOR_INFO, 126);
				StartNPCPlayback(GetPlayerID(targetPlayerName), recordingName, type, autoRepeat);
				return COMMAND_OK;
			}
			else
			{
				return COMMAND_ERROR;
			}
		}
		SendClientMessageEx(playerid, COLOR_INFO, 123, command);
		SendNPCCommand(GetPlayerID(targetPlayerName), command);
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
}