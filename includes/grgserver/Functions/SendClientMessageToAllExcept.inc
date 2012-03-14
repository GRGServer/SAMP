SendClientMessageToAllExcept(exceptPlayerID, color, message[])
{
	PlayerLoop(playerID)
	{
		if (playerID != exceptPlayerID && IsPlayerConnected(playerID))
		{
			SendClientMessage(playerID, color, message);
		}
	}
}