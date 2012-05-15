GetPlayerID(playerName[])
{
	PlayerLoop(playerID)
	{
		if (!strcmp(GetPlayerNameEx(playerID), playerName, true))
		{
			return playerID;
		}
	}
	return INVALID_PLAYER_ID;
}