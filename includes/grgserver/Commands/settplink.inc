PCMD:settplink[MAPPER](playerID, params[], StringID:406("Set the target of the selected LINK-pickup"))
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
		SendClientMessageEx(playerID, COLOR_INFO, StringID:408("The target for the teleport link %d has been set"), PVar:playerID[TELEPORT_LINKID]);
		return COMMAND_OK;
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:407("No teleport link selected!"));
		return COMMAND_ERROR;
	}
}