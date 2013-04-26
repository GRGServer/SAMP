PCMD:recnpc[NPCADMIN](playerid, params[], StringID:116("Create a new NPC recording"))
{
	new recordingType;
	new recordingName[STRINGLENGTH_NPCRECORDINGNAME];
	if (sscanf(params, "s[" #STRINGLENGTH_NPCRECORDINGNAME "]", recordingName))
	{
		CmdUsageMsg(playerid, "recnpc", "recordingName");
		return COMMAND_USAGE;
	}

	if (IsPlayerInAnyVehicle(playerid))
	{
		recordingType = PLAYER_RECORDING_TYPE_DRIVER;
	}
	else
	{
		recordingType = PLAYER_RECORDING_TYPE_ONFOOT;
	}

	StartRecordingPlayerData(playerid, recordingType, recordingName);
	SendClientMessageEx(playerid, COLOR_INFO, StringID:89("NPC Recording '%s' started"), recordingName);
	SendClientMessageEx(playerid, COLOR_INFO, StringID:90("Use /stoprec to stop"));
	return COMMAND_OK;
}