PCMD:god[ADMIN](playerID, params[], StringID:345("Give you infinite health"))
{
	if (PVar:playerID[GODMODE])
	{
		PVar:playerID[GODMODE] = false;
		SendClientMessageEx(playerID, COLOR_INFO, StringID:347("God mode disabled"));
	}
	else
	{
		PVar:playerID[GODMODE] = true;
		SendClientMessageEx(playerID, COLOR_INFO, StringID:346("God mode enabled"));
	}
	return COMMAND_OK;
}