PCMD:addpickup[MAPPER](playerID, params[], StringID:96(""))
{
	new type[256];
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	if (sscanf(params, "s[256]", type))
	{
		CmdUsageMsg(playerID, "addpickup", "Type");
		return COMMAND_USAGE;
	}
	type = strtoupper(type);
	if (IsValidPickupType(type))
	{
		GetPlayerPos(playerID, posX, posY, posZ);
		MySQLQuery("INSERT INTO `pickups` (`posX`, `posY`, `posZ`, `type`) VALUES('%f', '%f', '%f', '%s')", posX, posY, posZ, type);
		new pickupID = mysql_insert_id();
		if (pickupID)
		{
			if (AddPickup(pickupID, type, posX, posY, posZ))
			{
				SendClientMessageEx(playerID, COLOR_INFO, StringID:57(""), type, pickupID);
				return COMMAND_OK;
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, StringID:6(""));
			}
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:6(""));
		}
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:58(""));
	}
	return COMMAND_ERROR;
}