PCMD:stoprec[NPCADMIN](playerid, params[], "Aktuelle NPC Aufnahme beenden")
{
	StopRecordingPlayerData(playerid);
	SendClientMessage(playerid, COLOR_INFO, "Aufnahme gestoppt");
	return COMMAND_OK;
}