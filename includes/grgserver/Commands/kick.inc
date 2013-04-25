PCMD:kick[MODERATOR](playerID, params[], StringID:108("Kick a player from the server"))
{
	new targetPlayerID;
	new reason[256];
	if (sscanf(params, "us[256]", targetPlayerID, reason))
	{
		CmdUsageMsg(playerID, "kick", "PlayerID/Name", LanguageString(playerID, StringID:331("Reason")));
		return COMMAND_USAGE;
	}
	if (IsPlayerConnected(targetPlayerID))
	{
		printf("%s has been kicked by %s, Reason: %s", GetPlayerNameEx(targetPlayerID), GetPlayerNameEx(playerID), reason);
		PlayerLoop(loopPlayerID)
		{
			SendClientMessageEx(loopPlayerID, COLOR_ERROR, StringID:332("%p has been kicked by %p, Reason: %s"), targetPlayerID, playerID, reason);
		}
		Kick(targetPlayerID);
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
}