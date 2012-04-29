PCMD:setinterior[TELEPORT](playerID, params[], 348)
{
	new interiorID;
	if (sscanf(params, "d", interiorID))
	{
		CmdUsageMsg(playerID, "setinterior", "InteriorID");
		return COMMAND_USAGE;
	}
	SetPlayerInterior(playerID, interiorID);
	SendClientMessageEx(playerID, COLOR_INFO, 349, interiorID);
	return COMMAND_OK;
}