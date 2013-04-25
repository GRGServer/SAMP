PCMD:addteleport[TELEPORT](playerID, params[], StringID:333("Save your current location as teleport location"))
{
	new name[100];
	if (sscanf(params, "s[100]", name))
	{
		CmdUsageMsg(playerID, "addteleport", "Name");
		return COMMAND_USAGE;
	}
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:angle;
	GetPlayerPos(playerID, posX, posY, posZ);
	GetPlayerFacingAngle(playerID, angle);
	MySQLQuery("INSERT INTO `teleports` (`name`, `posX`, `posY`, `posZ`, `angle`, `interior`) VALUES('%s', '%f', '%f', '%f', '%f', '%d')", name, posX, posY, posZ, angle, GetPlayerInterior(playerID));
	SendClientMessageEx(playerID, COLOR_INFO, StringID:334("The teleport location has been saved. Use /teleport to teleport to the location"));
	return COMMAND_OK;
}