CMD:toggleclock(playerID, params[], 400)
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