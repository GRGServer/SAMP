CMD:getbalance(playerid, params[], 67)
{
	SendClientMessageEx(playerid, COLOR_INFO, 66, PVar:playerid[MONEY]);
	return COMMAND_OK;
}