PCMD:addinfopickup[MAPPER](playerID, params[], StringID:588("Add an info pickup"))
{
	new stringID;
	if (sscanf(params, "d", stringID))
	{
		CmdUsageMsg(playerID, "addinfopickup", "StringID");
		return COMMAND_USAGE;
	}
	if (stringID <= 0)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:587("The ID must be positive!"));
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
			SendClientMessageEx(playerID, COLOR_INFO, StringID:57("The pickup %s has been saved with ID %d"), "INFO", pickupID);
			return COMMAND_OK;
		}
	}
	SendClientMessageEx(playerID, COLOR_INFO, StringID:6("Error while creating the pickup!"));
	return COMMAND_ERROR;
}