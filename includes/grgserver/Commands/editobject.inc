PCMD:editobject[MAPPER](playerID, params[], 201)
{
	new objectID;
	if (sscanf(params, "d", objectID))
	{
		SelectObject(playerID);
		return COMMAND_OK;
	}

	if (objectID <= 0 || objectID > CountDynamicObjects() || Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID) != OBJECTTYPE_NORMAL)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 427);
		return COMMAND_ERROR;
	}

	new Float:posX;
	new Float:posY;
	new Float:posZ;
	GetDynamicObjectPos(objectID, posX, posY, posZ);
	OnPlayerSelectDynamicObject(playerID, objectID, Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_MODEL_ID), posX, posY, posZ);
	return COMMAND_OK;
}