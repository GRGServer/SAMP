PCMD:kick[MODERATOR](playerID, params[], 108)
{
	new targetPlayerID;
	new reason[256];
	if (sscanf(params, "us", targetPlayerID, reason))
	{
		CmdUsageMsg(playerID, "kick", "PlayerID/Name", LanguageString(playerID, 331));
		return COMMAND_USAGE;
	}
	if (IsPlayerConnected(targetPlayerID))
	{
		printf("%s has been kicked by %s, Reason: %s", GetPlayerNameEx(targetPlayerID), GetPlayerNameEx(playerID), reason);
		PlayerLoop(loopPlayerID)
		{
			SendClientMessageEx(loopPlayerID, COLOR_ERROR, 332, targetPlayerID, playerID, reason);
		}
		Kick(targetPlayerID);
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
}