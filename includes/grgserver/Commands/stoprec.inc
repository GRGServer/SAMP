PCMD:stoprec[NPCADMIN](playerID, params[], StringID:49("Stop the current NPC recording"))
{
	StopRecordingPlayerData(playerID);
	SendClientMessageEx(playerID, COLOR_INFO, StringID:48("Recording stopped"));
	return COMMAND_OK;
}