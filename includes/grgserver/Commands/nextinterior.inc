PCMD:nextinterior[TELEPORT](playerID, params[], StringID:402("Teleport to the next interior"))
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
	SendClientMessageEx(playerID, COLOR_INFO, StringID:405("You are now in interior %d"), PVar:playerID[CURRENTINTERIOR]);
	return COMMAND_OK;
}