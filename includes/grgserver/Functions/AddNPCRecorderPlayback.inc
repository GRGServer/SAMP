/*
	Description:
		Starts to play recording "recordingName" using NPC "NPC_<your-playername>".
		The NPC must be already connected!
	Parameters:
		playerID: The playerID of the player to use as the controller of the NPC
		recordingName: Name of the already existing NPC recording
		recordingType: Type of the NPC recording (PLAYER_RECORDING_TYPE_DRIVER or PLAYER_RECORDING_TYPE_ONFOOT)
	Return:
		true: Playback has been started
		false: An error occurred
*/
AddNPCRecorderPlayback(playerID, recordingName[], recordingType)
{
	FormatNew:npcPlayerName[MAX_PLAYER_NAME]("%s_NPC1", GetPlayerNameEx(playerID));
	new npcPlayerID = GetPlayerID(npcPlayerName);
	if (npcPlayerID == INVALID_PLAYER_ID)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 132, npcPlayerName, npcPlayerName);
	}
	else
	{
		if (recordingType == PLAYER_RECORDING_TYPE_DRIVER)
		{
			new vehicleID = GetVehicleBySaveID(strval(GetMySQLValue("npcs", "VehicleID", "Recording", recordingName)));
			if (vehicleID != INVALID_VEHICLE_ID)
			{
				PutPlayerInVehicle(npcPlayerID, vehicleID, 0);
			}
		}
		PVar:npcPlayerID[RECORDNPCFORPLAYER] = playerID;
		StartNPCPlayback(npcPlayerID, recordingName, recordingType, false);
		return true;
	}
	return false;
}