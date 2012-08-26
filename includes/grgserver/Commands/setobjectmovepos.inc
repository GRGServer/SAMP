PCMD:setobjectmovepos[MAPPER](playerID, params[], 463)
{
	if (!PVar:playerID[OBJEDITOR_CURRENTOBJECTID])
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 464);
		return COMMAND_ERROR;
	}
	new dbObjectID = Streamer_GetIntData(STREAMER_TYPE_OBJECT, PVar:playerID[OBJEDITOR_CURRENTOBJECTID], E_STREAMER_EXTRA_ID);
	if (dbObjectID <= 0)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 200);
		return COMMAND_ERROR;
	}
	new Float:speed;
	new timeout;
	if (sscanf(params, "fd", speed, timeout))
	{
		if (sscanf(params, "f", speed))
		{
			CmdUsageMsg(playerID, "setobjectmovepos", "Speed", "[Timeout]");
			return COMMAND_USAGE;
		}
	}
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:rotX;
	new Float:rotY;
	new Float:rotZ;
	GetDynamicObjectPos(PVar:playerID[OBJEDITOR_CURRENTOBJECTID], posX, posY, posZ);
	GetDynamicObjectRot(PVar:playerID[OBJEDITOR_CURRENTOBJECTID], rotX, rotY, rotZ);
	MySQLQuery("REPLACE INTO `moveobjects` (`objectId`, `posX`, `posY`, `posZ`, `rotX`, `rotY`, `rotZ`, `speed`, `timeout`) VALUES('%d', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%d')", dbObjectID, posX, posY, posZ, rotX, rotY, rotZ, speed, timeout);
	SendClientMessageEx(playerID, COLOR_INFO, 465, dbObjectID);
	return COMMAND_OK;
}