PCMD:reloadplayer[ADMIN](playerid, params[], StringID:117("Reload the data of a player from the database"))
{
	new targetPlayerID;
	if (sscanf(params, "u", targetPlayerID))
	{
		CmdUsageMsg(playerid, "reloadplayer", "PlayerID/Name");
		return COMMAND_USAGE;
	}
	if (targetPlayerID == INVALID_PLAYER_ID)
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
	LoadPlayer(targetPlayerID);
	return COMMAND_OK;
}