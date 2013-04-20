PCMD:kill[MODERATOR](playerID, params[], 197)
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
		SendClientMessageEx(targetPlayerID, COLOR_INFO, "195", playerID);
		SendClientMessageEx(playerID, COLOR_INFO, "196", targetPlayerID);
		SetPlayerHealth(targetPlayerID, 0.0);
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
}