CMD:pee(playerID, params[], CMD_PEE)
{
	if (PVar:playerID[PEE_TIMER])
	{
		PlayerPee(playerID, true);
	}
	else
	{
		PlayerPee(playerID, false);
	}

	return COMMAND_OK;
}