CMD:testunfreeze(playerid, params[], "Steuerungsbehinderung aufheben")
{
	TogglePlayerControllable(playerid, true);
	return COMMAND_OK;
}