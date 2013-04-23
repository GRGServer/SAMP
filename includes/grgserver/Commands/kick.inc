PCMD:kick[MODERATOR](playerID, params[], StringID:108(""))
{
	new targetPlayerID;
	new reason[256];
	if (sscanf(params, "us[256]", targetPlayerID, reason))
	{
		CmdUsageMsg(playerID, "kick", "PlayerID/Name", LanguageString(playerID, StringID:331("")));
		return COMMAND_USAGE;
	}
	if (IsPlayerConnected(targetPlayerID))
	{
		printf("%s has been kicked by %s, Reason: %s", GetPlayerNameEx(targetPlayerID), GetPlayerNameEx(playerID), reason);
		PlayerLoop(loopPlayerID)
		{
			SendClientMessageEx(loopPlayerID, COLOR_ERROR, StringID:332(""), targetPlayerID, playerID, reason);
		}
		Kick(targetPlayerID);
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
}