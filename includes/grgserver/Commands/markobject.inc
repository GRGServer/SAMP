PCMD:markobject[MAPPER](playerID, params[], 426)
{
	new objectID;
	if (sscanf(params, "d", objectID))
	{
		CmdUsageMsg(playerID, "markobject", "objectID");
		return COMMAND_USAGE;
	}

	if (objectID <= 0 || objectID > CountDynamicObjects() || Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID) != OBJECTTYPE_NORMAL)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 427);
		return COMMAND_ERROR;
	}

	SetPlayerMapIcon(playerID, 0, dynamicObjects[objectID - 1][OBJECT_POS][0], dynamicObjects[objectID - 1][OBJECT_POS][1], dynamicObjects[objectID - 1][OBJECT_POS][2], 0, COLOR_MARKER_OBJECT, MAPICON_GLOBAL);
	return COMMAND_OK;
}