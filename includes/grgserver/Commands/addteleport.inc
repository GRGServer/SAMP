PCMD:addteleport[TELEPORT](playerID, params[], StringID:333(""))
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
	SendClientMessageEx(playerID, COLOR_INFO, StringID:334(""));
	return COMMAND_OK;
}