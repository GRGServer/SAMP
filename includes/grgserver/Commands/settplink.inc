PCMD:settplink[MAPPER](playerID, params[], 406)
{
	if (PVar:playerID[TELEPORT_LINKID])
	{
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		new Float:angle;
		GetPlayerPos(playerID, posX, posY, posZ);
		GetPlayerFacingAngle(playerID, angle);
		MySQLQuery("UPDATE `tplinks` SET `posX` = '%f', `posY` = '%f', `posZ` = '%f', `angle` = '%f', `interior` = '%d' WHERE `id` = '%d'", posX, posY, posZ, angle, GetPlayerInterior(playerID), PVar:playerID[TELEPORT_LINKID]);
		SendClientMessageEx(playerID, COLOR_INFO, "408", PVar:playerID[TELEPORT_LINKID]);
		return COMMAND_OK;
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, "407");
		return COMMAND_ERROR;
	}
}