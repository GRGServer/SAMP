PCMD:god[ADMIN](playerID, params[], 345)
{
	if (PVar:playerID[GODMODE])
	{
		PVar:playerID[GODMODE] = false;
		SendClientMessageEx(playerID, COLOR_INFO, "347");
	}
	else
	{
		PVar:playerID[GODMODE] = true;
		SendClientMessageEx(playerID, COLOR_INFO, "346");
	}
	return COMMAND_OK;
}