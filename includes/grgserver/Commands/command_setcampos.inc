PCMD:setcampos[SERVERADMIN](playerID, params[], 181)
{
	new moveLook[10];
	new startStop[10];
	new time;
	if ((sscanf(params, "ssd", moveLook, startStop, time) && sscanf(params, "ss", moveLook, startStop)) || (strcmp(moveLook, "Move", true) && strcmp(moveLook, "Look", true)) || (strcmp(startStop, "Start", true) && strcmp(startStop, "End", true)))
	{
		CmdUsageMsg(playerID, "setcampos", "Move/Look", "Start/End", "[Time]");
		return COMMAND_USAGE;
	}
	if (!PVar:playerID[CAMERAMOVEMENT_EDITID])
	{
		if (!time)
		{
			time = 5000;
		}
		MySQLQuery("INSERT INTO `cameramovements` (`Time`) VALUES('%d')", time);
		PVar:playerID[CAMERAMOVEMENT_EDITID] = mysql_insert_id();
	}
	if (!PVar:playerID[CAMERAMOVEMENT_EDITID])
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 184);
		return COMMAND_ERROR;
	}
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	GetPlayerPos(playerID, posX, posY, posZ);
	MySQLQuery("UPDATE `cameramovements` SET `%s%sX` = '%f', `%s%sY` = '%f', `%s%sZ` = '%f' WHERE `ID` = '%d'", startStop, moveLook, posX, startStop, moveLook, posY, startStop, moveLook, posZ, PVar:playerID[CAMERAMOVEMENT_EDITID]);
	if (time)
	{
		MySQLQuery("UPDATE `cameramovements` SET `Time` = '%d' WHERE `ID` = '%d'", time, PVar:playerID[CAMERAMOVEMENT_EDITID]);
	}
	SendClientMessageEx(playerID, COLOR_INFO, 186, PVar:playerID[CAMERAMOVEMENT_EDITID]);
	return COMMAND_OK;
}