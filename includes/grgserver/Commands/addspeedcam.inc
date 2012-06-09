PCMD:addspeedcam[MAPPER](playerID, params[], 486)
{
	new speedLimit;
	if (sscanf(params, "d", speedLimit))
	{
		CmdUsageMsg(playerID, "addspeedcam", "SpeedLimit");
		return COMMAND_USAGE;
	}
	new objectID = AddObject(playerID, 18880);
	if (objectID)
	{
		new id = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID);
		MySQLQuery("INSERT INTO `speedcameras` (`objectId`, `speedLimit`) VALUES('%d', '%d')", id, speedLimit);
		return COMMAND_OK;
	}
	return COMMAND_ERROR;
}