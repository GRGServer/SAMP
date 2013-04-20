CMD:privatemessage(playerID, params[], 409)
{
	new targetPlayerID;
	new message[128];
	if (sscanf(params, "us", targetPlayerID, message))
	{
		CmdUsageMsg(playerID, "privatemessage", "PlayerID/Name", "Text");
		return COMMAND_USAGE;
	}
	if (targetPlayerID == INVALID_PLAYER_ID)
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
	if (playerID == targetPlayerID)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, "454");
		return COMMAND_ERROR;
	}
	SendMessageToChannel(playerID, "PLAYER", message, targetPlayerID);
	return COMMAND_OK;
}