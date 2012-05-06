PCMD:maptp[TELEPORT](playerID, params[], 263)
{
	if (PVar:playerID[MAP_POSX] && PVar:playerID[MAP_POSY])
	{
		SetPlayerPosFindZ(playerID, PVar:playerID[MAP_POSX], PVar:playerID[MAP_POSY], 6000.0);
		SetTimerEx("Timer_SetPlayerPosFindZ", 500, false, "dfff", playerID, PVar:playerID[MAP_POSX], PVar:playerID[MAP_POSY], 6000.0);// Workaround for http://forum.sa-mp.com/showthread.php?p=1800073
		SendClientMessageEx(playerID, COLOR_INFO, 144);
		return COMMAND_OK;
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 264);
	}
	return COMMAND_ERROR;
}