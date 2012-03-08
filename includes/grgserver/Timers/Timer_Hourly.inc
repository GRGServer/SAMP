Timer:Hourly()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		UpdateGasPrice();
		UpdatePayDay(i);
	}
}