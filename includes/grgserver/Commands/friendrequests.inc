CMD:friendrequests(playerID, params[], StringID:479("See your current friendship requests"))
{
	if (ShowDialog:FriendRequests(playerID))
	{
		return COMMAND_OK;
	}
	SendClientMessageEx(playerID, COLOR_ERROR, StringID:497("There are currently no friendship requests!"));
	return COMMAND_ERROR;
}