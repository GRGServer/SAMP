PCMD:addinfopickup[MAPPER](playerID, params[], 588)
{
	new stringID;
	if (sscanf(params, "d", stringID))
	{
		CmdUsageMsg(playerID, "addinfopickup", "StringID");
		return COMMAND_USAGE;
	}
	if (stringID <= 0)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 587);
		return COMMAND_ERROR;
	}
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	GetPlayerPos(playerID, posX, posY, posZ);
	MySQLQuery("INSERT INTO `pickups` (`posX`, `posY`, `posZ`, `type`) VALUES('%f', '%f', '%f', 'INFO')", posX, posY, posZ);
	new pickupID = mysql_insert_id();
	if (pickupID)
	{
		MySQLQuery("INSERT INTO `infopickups` (`pickupId`, `stringId`) VALUES('%d', '%d')", pickupID, stringID);
		if (AddPickup(pickupID, "INFO", posX, posY, posZ))
		{
			SendClientMessageEx(playerID, COLOR_INFO, 57, "INFO", pickupID);
			return COMMAND_OK;
		}
	}
	SendClientMessageEx(playerID, COLOR_INFO, 6);
	return COMMAND_ERROR;
}