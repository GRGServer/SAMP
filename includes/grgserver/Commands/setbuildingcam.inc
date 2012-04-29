PCMD:setbuildingcam[MAPPER](playerID, params[], 336)
{
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	if (PVar:playerID[SELECTEDBUILDINGID])
	{
		GetPlayerCameraPos(playerID, posX, posY, posZ);
		MySQLQuery("UPDATE `buildings` SET `CameraPosX` = '%f', `CameraPosY` = '%f', `CameraPosZ` = '%f' WHERE `ID` = '%d'", posX, posY, posZ, PVar:playerID[SELECTEDBUILDINGID]);
		SendClientMessageEx(playerID, COLOR_INFO, 29);
		return COMMAND_OK;
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 34);
		return COMMAND_ERROR;
	}
}