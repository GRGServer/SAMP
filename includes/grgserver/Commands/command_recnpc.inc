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