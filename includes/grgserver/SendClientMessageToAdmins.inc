SendClientMessageToAdmins(permission, color, message[])
{
	for (new playerID = 0; playerID < MAX_PLAYERS; playerID++)
	{
		if (IsPlayerConnected(playerID) && permissions[playerID][enum_permission:permission])
		{
			SendClientMessage(playerID, color, message);
		}
	}
}