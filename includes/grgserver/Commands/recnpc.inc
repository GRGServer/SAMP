PCMD:recnpc[NPCADMIN](playerid, params[], 116)
{
	new npcs;
	new recordingType;
	new recordingName[256];
	new playbackName1[256];
	new playbackName2[256];
	new playbackName3[256];
	if (sscanf(params, "s[256]s[256]s[256]s[256]", recordingName, playbackName1, playbackName2, playbackName3))
	{
		if (sscanf(params, "s[256]s[256]s[256]", recordingName, playbackName1, playbackName2))
		{
			if (sscanf(params, "s[256]s[256]", recordingName, playbackName1))
			{
				if (sscanf(params, "s[256]", recordingName))
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
	SendClientMessageEx(playerid, COLOR_INFO, "89", recordingName, npcs);
	SendClientMessageEx(playerid, COLOR_INFO, "90");
	return COMMAND_OK;
}