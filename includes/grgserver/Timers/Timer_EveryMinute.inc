Timer:EveryMinute()
{
	PlayerLoop(playerID)
	{
		PVar:playerID[SAVENOW] = IsLoggedIn(playerID);
	}
}