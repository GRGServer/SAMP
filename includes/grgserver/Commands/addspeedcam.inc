PCMD:addspeedcam[MAPPER](playerID, params[], 486)
{
	new speedLimit;
	if (sscanf(params, "d", speedLimit))
	{
		CmdUsageMsg(playerID, "addspeedcam", "SpeedLimit");
		return COMMAND_USAGE;
	}
	new objectID = AddObject(playerID, 18880, "speedcameras");
	if (objectID)
	{
		MySQLQuery("INSERT INTO `speedcameras` (`objectId`, `speedLimit`) VALUES('%d', '%d')", dynamicObjects[objectID - 1][OBJECT_ID], speedLimit);
		return COMMAND_OK;
	}
	return COMMAND_ERROR;
}