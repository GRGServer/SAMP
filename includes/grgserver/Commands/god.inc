PCMD:god[ADMIN](playerID, params[], StringID:345(""))
{
	if (PVar:playerID[GODMODE])
	{
		PVar:playerID[GODMODE] = false;
		SendClientMessageEx(playerID, COLOR_INFO, StringID:347(""));
	}
	else
	{
		PVar:playerID[GODMODE] = true;
		SendClientMessageEx(playerID, COLOR_INFO, StringID:346(""));
	}
	return COMMAND_OK;
}