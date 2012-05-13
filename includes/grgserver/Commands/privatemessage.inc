CMD:privatemessage(playerID, params[], 409)
{
	new targetPlayerID;
	new text[128];
	if (sscanf(params, "us", targetPlayerID, text))
	{
		CmdUsageMsg(playerID, "privatemessage", "PlayerID/Name", "Text");
		return COMMAND_USAGE;
	}
	if (targetPlayerID == INVALID_PLAYER_ID)
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
	SendClientMessageEx(targetPlayerID, COLOR_PM, 410, playerID, text);
	SendClientMessageEx(playerID, COLOR_PM, 411, targetPlayerID, text);
	return COMMAND_OK;
}