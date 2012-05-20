PCMD:editobject[MAPPER](playerID, params[], 201)
{
	new dbObjectID;
	if (sscanf(params, "d", dbObjectID))
	{
		SelectObject(playerID);
		return COMMAND_OK;
	}
	new objectID = GetObjectByID(dbObjectID);
	if (!objectID)
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