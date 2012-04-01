PCMD:newcammovement[SERVERADMIN](playerID, params[], 181)
{
	new time;
	sscanf(params, "d", time);
	if (!time)
	{
		time = 5000;
	}
	MySQLQuery("INSERT INTO `cameramovements` (`Time`) VALUES('%d')", time);
	PVar:playerID[CAMERAMOVEMENT_EDITID] = mysql_insert_id();
	if (!PVar:playerID[CAMERAMOVEMENT_EDITID])
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 184);
		return COMMAND_ERROR;
	}
	SendClientMessageEx(playerID, COLOR_INFO, 185, PVar:playerID[CAMERAMOVEMENT_EDITID]);
	return COMMAND_OK;
}