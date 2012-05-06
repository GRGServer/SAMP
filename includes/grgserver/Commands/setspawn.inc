PCMD:setspawn[MAPPER](playerID, params[], 401)
{
	if (!PVar:playerID[CURRENTINTERIOR])
	{
		SendClientMessageEx(playerID, COLOR_INFO, 404);
		return COMMAND_ERROR;
	}
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:angle;
	GetPlayerPos(playerID, posX, posY, posZ);
	GetPlayerFacingAngle(playerID, angle);
	MySQLQuery("UPDATE `interiors` SET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Angle` = '%f' WHERE `ID` = '%d'", posX, posY, posZ, angle, PVar:playerID[CURRENTINTERIOR]);
	SendClientMessageEx(playerID, COLOR_INFO, 403);
	return COMMAND_OK;
}