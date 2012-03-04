CMD:exit(playerid, params[], "Gebäude verlassen")
{
	if (GetPVar:playerid[SHOWINTERIOR_OLDINTERIOR] == -1)
	{
		if (LeaveBuilding(playerid))
		{
			return COMMAND_OK;
		}
		else
		{
			SendClientMessage(playerid, COLOR_ERROR, "Du bist in keinem Haus!");
			return COMMAND_ERROR;
		}
	}
	else
	{
		SetPlayerPos(playerid, GetPVar:playerid[SHOWINTERIOR_OLDPOSX], GetPVar:playerid[SHOWINTERIOR_OLDPOSY], GetPVar:playerid[SHOWINTERIOR_OLDPOSZ]);
		SetPlayerInterior(playerid, GetPVar:playerid[SHOWINTERIOR_OLDINTERIOR]);
		SetPVar:playerid[SHOWINTERIOR_OLDINTERIOR](-1);
		return COMMAND_OK;
	}
}