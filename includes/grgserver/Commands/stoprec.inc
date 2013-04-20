PCMD:stoprec[NPCADMIN](playerid, params[], 49)
{
	StopRecordingPlayerData(playerid);
	SendClientMessageEx(playerid, COLOR_INFO, "48");
	return COMMAND_OK;
}