AddNPCRecorderPlayback(playerID, recordingName[], recordingType)
{
	new npcPlayerName[MAX_PLAYER_NAME];
	format(npcPlayerName, sizeof(npcPlayerName), "%s_NPC1", GetPlayerNameEx(playerID));
	new npcPlayerID = GetPlayerID(npcPlayerName);
	if (npcPlayerID == INVALID_PLAYER_ID)
	{
		new string[256];
		format(string, sizeof(string), "Der NPC '%s' ist nicht verbunden! Verwende /controlnpc %s connect und versuche es erneut.", npcPlayerName, npcPlayerName);
		SendClientMessage(playerID, COLOR_ERROR, string);
	}
	else
	{
		if (recordingType == PLAYER_RECORDING_TYPE_DRIVER)
		{
			new modelID = strval(GetMySQLValue("npcs", "VehicleModelID", "Recording", recordingName));
			if (modelID)
			{
				PutPlayerInVehicle(npcPlayerID, CreateVehicle(modelID, 0.0, 0.0, 0.0, 0.0, random(126), random(126), 1), 0);
			}
		}
		SetPVarInt(npcPlayerID, "RecordNPCForPlayer", playerID);
		StartNPCPlayback(npcPlayerID, recordingName, recordingType, false);
		return true;
	}
	return false;
}

SendNPCCommand(npcPlayerID, command[])
{
	SendClientMessage(npcPlayerID, COLOR_NPCCOMMAND, command);
}

StartNPCPlayback(npcPlayerID, recordingName[], recordingType, autoRepeat)
{
	new string[256];
	format(string, sizeof(string), "%s %d %d", recordingName, recordingType, autoRepeat);
	SendClientMessage(npcPlayerID, COLOR_NPCCOMMAND, string);
}