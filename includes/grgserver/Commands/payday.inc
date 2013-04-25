CMD:payday(playerID, params[], StringID:114("Show information about the pay day"))
{
	ShowDialog:PaydayInfo(playerID);
	return COMMAND_OK;
}