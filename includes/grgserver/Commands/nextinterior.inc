PCMD:nextinterior[TELEPORT](playerID, params[], 402)
{
	new interiorID;
	sscanf(params, "d", interiorID);
	if (interiorID)
	{
		PVar:playerID[CURRENTINTERIOR] = interiorID;
	}
	else
	{
		PVar:playerID[CURRENTINTERIOR]++;
	}
	if (!TeleportToInterior(playerID, PVar:playerID[CURRENTINTERIOR]))
	{
		TeleportToInterior(playerID, 1);
	}
	SendClientMessageEx(playerID, COLOR_INFO, 405, PVar:playerID[CURRENTINTERIOR]);
	return COMMAND_OK;
}