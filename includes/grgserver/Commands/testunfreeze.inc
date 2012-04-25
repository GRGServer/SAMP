CMD:testunfreeze(playerid, params[], 0)
{
	TogglePlayerControllable(playerid, true);
	return COMMAND_OK;
}