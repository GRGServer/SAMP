PCMD:stoprec[NPCADMIN](playerid, params[], StringID:49("Stop the current NPC recording"))
{
	StopRecordingPlayerData(playerid);
	SendClientMessageEx(playerid, COLOR_INFO, StringID:48("Recording stopped"));
	return COMMAND_OK;
}