PCMD:ban[MODERATOR](playerID, params[], 471)
{
	new targetPlayerID;
	new reason[256];
	if (sscanf(params, "us", targetPlayerID, reason))
	{
		CmdUsageMsg(playerID, "ban", "PlayerID/Name", LanguageString(playerID, "331"));
		return COMMAND_USAGE;
	}
	if (!IsPlayerConnected(targetPlayerID))
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
	PlayerLoop(loopPlayerID)
	{
		SendClientMessageEx(loopPlayerID, COLOR_ERROR, "472", targetPlayerID, playerID, reason);
	}
	MySQLBan(playerID, targetPlayerID, reason, true);
	return COMMAND_OK;
}