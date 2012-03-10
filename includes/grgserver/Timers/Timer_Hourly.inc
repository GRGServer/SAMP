Timer:Hourly()
{
	UpdateGasPrice();
	Count(playerID, MAX_PLAYERS)
	{
		UpdatePayDay(playerID);
	}
}