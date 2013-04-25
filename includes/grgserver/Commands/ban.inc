PCMD:ban[MODERATOR](playerID, params[], StringID:471("Ban a player"))
{
	new targetPlayerID;
	new reason[256];
	if (sscanf(params, "us", targetPlayerID, reason))
	{
		CmdUsageMsg(playerID, "ban", "PlayerID/Name", LanguageString(playerID, StringID:331("Reason")));
		return COMMAND_USAGE;
	}
	if (!IsPlayerConnected(targetPlayerID))
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
	PlayerLoop(loopPlayerID)
	{
		SendClientMessageEx(loopPlayerID, COLOR_ERROR, StringID:472("%p has been banned by %p, Reason: %s"), targetPlayerID, playerID, reason);
	}
	MySQLBan(playerID, targetPlayerID, reason, true);
	return COMMAND_OK;
}