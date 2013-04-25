PCMD:selectlastobject[MAPPER](playerID, params[], StringID:398("Select your last added object"))
{
	new objectID = PVar:playerID[LASTOBJECT];
	if (objectID)
	{
		OnPlayerSelectDynamicObject(playerID, objectID, Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_MODEL_ID), dynamicObjects[objectID - 1][OBJECT_POS][0], dynamicObjects[objectID - 1][OBJECT_POS][1], dynamicObjects[objectID - 1][OBJECT_POS][2]);
		return COMMAND_OK;
	}

	SendClientMessageEx(playerID, COLOR_ERROR, StringID:425("No object found!"));
	return COMMAND_ERROR;
}