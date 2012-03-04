Timer:EveryMinute()
{
	for (new playerID = 0; playerID < MAX_PLAYERS; playerID++)
	{
		savePlayers[playerID] = IsLoggedIn(playerID);
	}
}