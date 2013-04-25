PCMD:setpropertycam[MAPPER](playerID, params[], StringID:336("Set the 'Property bought' camera position"))
{
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	if (PVar:playerID[SELECTEDPROPERTYID])
	{
		GetPlayerCameraPos(playerID, posX, posY, posZ);
		MySQLQuery("UPDATE `properties` SET `cameraPosX` = '%f', `cameraPosY` = '%f', `cameraPosZ` = '%f' WHERE `id` = '%d'", posX, posY, posZ, PVar:playerID[SELECTEDPROPERTYID]);
		SendClientMessageEx(playerID, COLOR_INFO, StringID:29("Camera position saved"));
		return COMMAND_OK;
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:34("No property selected! Go into a property pickup and press ~k~~SNEAK_ABOUT~ to select it."));
		return COMMAND_ERROR;
	}
}