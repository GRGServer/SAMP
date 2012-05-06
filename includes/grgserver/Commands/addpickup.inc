PCMD:addpickup[MAPPER](playerID, params[], 96)
{
	new type[256];
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	if (sscanf(params, "s", type))
	{
		CmdUsageMsg(playerID, "addpickup", "Type");
		return COMMAND_USAGE;
	}
	type = strtoupper(type);
	if (IsValidPickupType(type))
	{
		GetPlayerPos(playerID, posX, posY, posZ);
		new id = AddPickup(-1, type, posX, posY, posZ, true);
		if (id > 0)
		{
			SendClientMessageEx(playerID, COLOR_INFO, 57, type, id);
			return COMMAND_OK;
		}
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 58);
	}
	return COMMAND_ERROR;
}