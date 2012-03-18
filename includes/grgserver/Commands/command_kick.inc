PCMD:kick[MODERATOR](playerid, params[], 108)
{
	new targetPlayerID;
	new string[256];
	if (sscanf(params, "us", targetPlayerID, string))
	{
		CmdUsageMsg(playerid, "kick", "Spielername/ID", "Grund");
		return COMMAND_USAGE;
	}
	if (IsPlayerConnected(targetPlayerID))
	{
		Kick(targetPlayerID);
		printf("%s has been kicked by %s, Reason: %s", GetPlayerNameEx(targetPlayerID), GetPlayerNameEx(playerid), string);
		Format:string("%s wurde von %s gekickt, Grund: %s", GetPlayerNameEx(targetPlayerID), GetPlayerNameEx(playerid), string);
		SendClientMessageToAll(COLOR_ERROR, string);
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
}