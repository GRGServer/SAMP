CMD:teststart(playerID, params[], 0)
{
	TogglePlayerControllable(playerID, false);
	StartScreenFader(playerID, 0, 0, 0, 2, 500, FADE_START_INPLANE1_BLACK);
	return COMMAND_OK;
}