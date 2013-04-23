CMD:friendrequests(playerID, params[], StringID:479(""))
{
	if (ShowDialog:FriendRequests(playerID))
	{
		return COMMAND_OK;
	}
	SendClientMessageEx(playerID, COLOR_ERROR, StringID:497(""));
	return COMMAND_ERROR;
}