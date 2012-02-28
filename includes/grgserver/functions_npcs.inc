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
				PutPlayerInVehicle(npcPlayerID, CreateVehicle(modelID, 0.0, 0.0, 0.0, 0.0, random(127), random(127), 1), 0);
			}
		}
		SetPVarInt(npcPlayerID, "RecordNPCForPlayer", playerID);
		StartNPCPlayback(npcPlayerID, recordingName, recordingType, false);
		return true;
	}
	return false;
}

ReconnectNPCs()
{
	for (new playerID = 0; playerID < MAX_PLAYERS; playerID++)
	{
		if (IsPlayerNPC(playerID))
		{
			Kick(playerID);
		}
	}
	mysql_query("SELECT * FROM `npcs` WHERE `AutoConnect` = '1'");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		FormatNew:npcName[MAX_PLAYER_NAME]("NPC_%s", GetMySQLField("Name"));
		ConnectNPC(npcName, NPC_SCRIPTNAME);
	}
	mysql_free_result();
}

SendNPCCommand(npcPlayerID, command[])
{
	SendClientMessage(npcPlayerID, COLOR_NPCCOMMAND, command);
}

StartNPCPlayback(npcPlayerID, recordingName[], recordingType, autoRepeat)
{
	new string[256];
	Format:string("%s %d %d", recordingName, recordingType, autoRepeat);
	SendClientMessage(npcPlayerID, COLOR_NPCCOMMAND, string);
}