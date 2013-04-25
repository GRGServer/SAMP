CMD:toggleclock(playerID, params[], StringID:400("Toggle the clock in the top right corner"))
{
	if (PVar:playerID[SHOWCLOCK])
	{
		PVar:playerID[SHOWCLOCK] = false;
		TextDrawHideForPlayer(playerID, textDrawClock);
	}
	else
	{
		PVar:playerID[SHOWCLOCK] = true;
		TextDrawShowForPlayer(playerID, textDrawClock);
	}
	return COMMAND_OK;
}