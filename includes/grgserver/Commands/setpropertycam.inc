PCMD:setpropertycam[MAPPER](playerID, params[], 336)
{
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	if (PVar:playerID[SELECTEDPROPERTYID])
	{
		GetPlayerCameraPos(playerID, posX, posY, posZ);
		MySQLQuery("UPDATE `properties` SET `cameraPosX` = '%f', `cameraPosY` = '%f', `cameraPosZ` = '%f' WHERE `id` = '%d'", posX, posY, posZ, PVar:playerID[SELECTEDPROPERTYID]);
		SendClientMessageEx(playerID, COLOR_INFO, 29);
		return COMMAND_OK;
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 34);
		return COMMAND_ERROR;
	}
}