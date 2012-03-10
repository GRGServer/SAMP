AddNPCRecorderPlayback(playerID, recordingName[], recordingType)
{
	FormatNew:npcPlayerName[MAX_PLAYER_NAME]("%s_NPC1", GetPlayerNameEx(playerID));
	new npcPlayerID = GetPlayerID(npcPlayerName);
	if (npcPlayerID == INVALID_PLAYER_ID)
	{
		FormatNew:string[140]("Der NPC '%s' ist nicht verbunden! Verwende /controlnpc %s connect und versuche es erneut.", npcPlayerName, npcPlayerName);
		SendClientMessage(playerID, COLOR_ERROR, string);
	}
	else
	{
		if (recordingType == PLAYER_RECORDING_TYPE_DRIVER)
		{
			new modelID = strval(GetMySQLValue("npcs", "VehicleModelID", "Recording", recordingName));
			if (modelID)
			{
				PutPlayerInVehicle(npcPlayerID, CreateVehicleEx(modelID, 0.0, 0.0, 0.0, 0.0, random(127), random(127), 0), 0);
			}
		}
		PVar:npcPlayerID[RECORDNPCFORPLAYER] = playerID;
		StartNPCPlayback(npcPlayerID, recordingName, recordingType, false);
		return true;
	}
	return false;
}