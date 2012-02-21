PCMD:kick[MODERATOR](playerid, params[])
{
	new targetPlayerID;
	new reason[256];
	new string[256];
	if (sscanf(params, "us", targetPlayerID, reason))
	{
		CmdUsageMsg(playerid, "kick", "Spielername/ID", "Grund");
		return COMMAND_USAGE;
	}
	if (IsPlayerConnected(targetPlayerID))
	{
		Kick(targetPlayerID);
		format(string, sizeof(string), "%s wurde von %s gekickt, Grund: %s", GetPlayerNameEx(targetPlayerID), GetPlayerNameEx(playerid), reason);
		SendClientMessageToAll(COLOR_ERROR, string);
		printf("%s has been kicked by %s, Reason: %s", GetPlayerNameEx(targetPlayerID), GetPlayerNameEx(playerid), reason);
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
}