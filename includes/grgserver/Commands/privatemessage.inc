CMD:privatemessage(playerID, params[], StringID:409("Send a private message to another player"))
{
	new targetPlayerID;
	new message[128];
	if (sscanf(params, "us[128]", targetPlayerID, message))
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
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:454("What sense does it make to send yourself a private message?"));
		return COMMAND_ERROR;
	}
	SendMessageToChannel(playerID, "PLAYER", message, targetPlayerID);
	return COMMAND_OK;
}