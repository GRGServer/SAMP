Timer:Hourly()
{
	UpdateGasPrice();
	Count(playerID, MAX_PLAYERS)
	{
		PVar:playerID[PAYDAY] = IsLoggedIn(playerID);
	}
}