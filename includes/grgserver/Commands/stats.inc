CMD:stats(playerID, params[], StringID:120("Show information about your player"))
{
	ShowDialog:Stats(playerID);
	return COMMAND_OK;
}