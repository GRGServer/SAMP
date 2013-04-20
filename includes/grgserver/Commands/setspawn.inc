PCMD:setspawn[MAPPER](playerID, params[], 401)
{
	if (!PVar:playerID[CURRENTINTERIOR])
	{
		SendClientMessageEx(playerID, COLOR_INFO, "404");
		return COMMAND_ERROR;
	}
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:angle;
	GetPlayerPos(playerID, posX, posY, posZ);
	GetPlayerFacingAngle(playerID, angle);
	MySQLQuery("UPDATE `interiors` SET `posX` = '%f', `posY` = '%f', `posZ` = '%f', `angle` = '%f' WHERE `id` = '%d'", posX, posY, posZ, angle, PVar:playerID[CURRENTINTERIOR]);
	SendClientMessageEx(playerID, COLOR_INFO, "403");
	return COMMAND_OK;
}