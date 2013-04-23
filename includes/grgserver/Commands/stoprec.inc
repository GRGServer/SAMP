PCMD:stoprec[NPCADMIN](playerid, params[], StringID:49(""))
{
	StopRecordingPlayerData(playerid);
	SendClientMessageEx(playerid, COLOR_INFO, StringID:48(""));
	return COMMAND_OK;
}