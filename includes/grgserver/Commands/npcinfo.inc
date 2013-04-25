PCMD:npcinfo[NPCADMIN](playerID, params[], StringID:573("Show information about a NPC"))
{
	new npcPlayerID;
	if (sscanf(params, "u", npcPlayerID))
	{
		CmdUsageMsg(playerID, "npcinfo", "PlayerID/Name");
		return COMMAND_USAGE;
	}
	if (npcPlayerID == INVALID_PLAYER_ID)
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
	if (!IsPlayerNPC(npcPlayerID))
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:571("%p is not a NPC!"), npcPlayerID);
		return COMMAND_ERROR;
	}
	SendClientMessageEx(playerID, COLOR_INFO, StringID:572("Last recording length: %s seconds"), FormatNumber(PVar:npcPlayerID[NPC_RECORDINGLENGTH]));
	return COMMAND_OK;
}