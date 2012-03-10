Timer:EveryMinute()
{
	for (new playerID = 0; playerID < MAX_PLAYERS; playerID++)
	{
		PVar:playerID[SAVENOW] = IsLoggedIn(playerID);
	}
}