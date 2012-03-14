SendClientMessageToAdmins(permission, color, message[])
{
	PlayerLoop(playerID)
	{
		if (IsPlayerConnected(playerID) && permissions[playerID][enum_permission:permission])
		{
			SendClientMessage(playerID, color, message);
		}
	}
}