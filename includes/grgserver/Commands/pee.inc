CMD:pee(playerID, params[], CMD_PEE)
{
	if (PVar:playerID[PEE_TIMER])
	{
		PlayerPee(playerID, false);
	}
	else
	{
		PlayerPee(playerID, true);
	}

	return COMMAND_OK;
}