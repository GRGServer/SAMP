PCMD:kill[MODERATOR](playerID, params[], StringID:197(""))
{
	new targetPlayerID;
	if (sscanf(params, "u", targetPlayerID))
	{
		CmdUsageMsg(playerID, "kill", "Playername/ID");
		return COMMAND_USAGE;
	}
	if (IsPlayerConnected(targetPlayerID))
	{
		printf("%s has been killed by %s", GetPlayerNameEx(targetPlayerID), GetPlayerNameEx(playerID));
		SendClientMessageEx(targetPlayerID, COLOR_INFO, StringID:195(""), playerID);
		SendClientMessageEx(playerID, COLOR_INFO, StringID:196(""), targetPlayerID);
		SetPlayerHealth(targetPlayerID, 0.0);
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
}