PCMD:addteleport[TELEPORT](playerID, params[], 333)
{
	new name[100];
	if (sscanf(params, "s", name))
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
	MySQLQuery("INSERT INTO `teleports` (`Name`, `PosX`, `PosY`, `PosZ`, `Angle`, `Interior`) VALUES('%s', '%f', '%f', '%f', '%f', '%d')", name, posX, posY, posZ, angle, GetPlayerInterior(playerID));
	SendClientMessageEx(playerID, COLOR_INFO, 334);
	return COMMAND_OK;
}