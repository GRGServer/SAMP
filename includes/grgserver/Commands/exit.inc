CMD:exit(playerid, params[], StringID:101("Leave the current building"))
{
	if (PVar:playerid[SHOWINTERIOR_OLDINTERIOR] == -1)
	{
		if (LeaveProperty(playerid))
		{
			return COMMAND_OK;
		}
		else
		{
			SendClientMessageEx(playerid, COLOR_ERROR, StringID:61("You are not in a building!"));
			return COMMAND_ERROR;
		}
	}
	else
	{
		SetPlayerPosEx(playerid, PVar:playerid[SHOWINTERIOR_OLDPOSX], PVar:playerid[SHOWINTERIOR_OLDPOSY], PVar:playerid[SHOWINTERIOR_OLDPOSZ]);
		SetPlayerInterior(playerid, PVar:playerid[SHOWINTERIOR_OLDINTERIOR]);
		PVar:playerid[SHOWINTERIOR_OLDINTERIOR] = -1;
		return COMMAND_OK;
	}
}