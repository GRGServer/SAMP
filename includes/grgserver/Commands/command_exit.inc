CMD:exit(playerid, params[], 101)
{
	if (PVar:playerid[SHOWINTERIOR_OLDINTERIOR] == -1)
	{
		if (LeaveBuilding(playerid))
		{
			return COMMAND_OK;
		}
		else
		{
			SendClientMessageEx(playerid, COLOR_ERROR, 61);
			return COMMAND_ERROR;
		}
	}
	else
	{
		SetPlayerPos(playerid, PVar:playerid[SHOWINTERIOR_OLDPOSX], PVar:playerid[SHOWINTERIOR_OLDPOSY], PVar:playerid[SHOWINTERIOR_OLDPOSZ]);
		SetPlayerInterior(playerid, PVar:playerid[SHOWINTERIOR_OLDINTERIOR]);
		PVar:playerid[SHOWINTERIOR_OLDINTERIOR] = -1;
		return COMMAND_OK;
	}
}