PCMD:coordtp[TELEPORT](playerID, params[], StringID:326("Teleport you to the specified coordinates"))
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
	SendClientMessageEx(playerID, COLOR_INFO, StringID:144("You got teleported"));
	return COMMAND_OK;
}