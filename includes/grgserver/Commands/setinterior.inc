PCMD:setinterior[TELEPORT](playerID, params[], StringID:348("Change your current interior"))
{
	new interiorID;
	if (sscanf(params, "d", interiorID))
	{
		CmdUsageMsg(playerID, "setinterior", "InteriorID");
		return COMMAND_USAGE;
	}
	SetPlayerInterior(playerID, interiorID);
	SendClientMessageEx(playerID, COLOR_INFO, StringID:349("Interior changed to %d"), interiorID);
	return COMMAND_OK;
}