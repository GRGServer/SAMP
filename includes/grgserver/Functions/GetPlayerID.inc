GetPlayerID(playerName[])
{
	for (new playerID; playerID < MAX_PLAYERS; playerID++)
	{
		if (IsPlayerConnected(playerID))
		{
			if (!strcmp(GetPlayerNameEx(playerID), playerName, true))
			{
				return playerID;
			}
		}
	}
	return INVALID_PLAYER_ID;
}