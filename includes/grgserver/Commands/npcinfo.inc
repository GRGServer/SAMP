PCMD:npcinfo[NPCADMIN](playerID, params[], 573)
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
		SendClientMessageEx(playerID, COLOR_ERROR, "571", npcPlayerID);
		return COMMAND_ERROR;
	}
	SendClientMessageEx(playerID, COLOR_INFO, "572", FormatNumber(PVar:npcPlayerID[NPC_RECORDINGLENGTH]));
	return COMMAND_OK;
}