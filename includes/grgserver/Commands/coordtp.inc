PCMD:coordtp[TELEPORT](playerID, params[], 326)
{
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	if (sscanf(params, "fff", posX, posY, posZ))
	{
		CmdUsageMsg(playerID, "coordtp", "X", "Y", "Z");
		return COMMAND_USAGE;
	}
	SetPlayerPosFindZ(playerID, posX, posY, posZ);
	SendClientMessageEx(playerID, COLOR_INFO, "144");
	return COMMAND_OK;
}