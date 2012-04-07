PCMD:addobject[MAPPER](playerID, params[], 202)
{
	new modelID;
	if (sscanf(params, "d", modelID))
	{
		new modelName[100];
		if (sscanf(params, "s", modelName))
		{
			CmdUsageMsg(playerID, "addobject", "modelID/ModelName");
			return COMMAND_USAGE;
		}
		// TODO: Convert name to ID
	}
	if (modelID != -1)
	{
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		new interior = GetPlayerInterior(playerID);
		GetPlayerPos(playerID, posX, posY, posZ);
		MySQLQuery("INSERT INTO `objects` (`ModelID`, `PosX`, `PosY`, `PosZ`, `Interior`, `Source`) VALUES('%d', '%f', '%f', '%f', '%d', 'Ingame')", modelID, posX, posY, posZ, interior);
		new objectID = CreateDynamicObject(modelID, posX, posY, posZ, 0.0, 0.0, 0.0, -1, interior, -1, 100.0);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID, mysql_insert_id());
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_ERROR;
	}
}