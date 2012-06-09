CMD:friendrequests(playerID, params[], 479)
{
	if (ShowDialog:FriendRequests(playerID))
	{
		return COMMAND_OK;
	}
	SendClientMessageEx(playerID, COLOR_ERROR, 497);
	return COMMAND_ERROR;
}