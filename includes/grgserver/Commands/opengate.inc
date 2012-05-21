CMD:opengate(playerID, params[], 467)
{
	new Float:distance;
	new objectID = GetClosestGate(playerID, distance);
	if (!objectID || distance > 15)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 468);
		return COMMAND_ERROR;
	}
	new dbObjectID = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID);
	if (!CheckGatePermission(playerID, dbObjectID))
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 469);
		return COMMAND_ERROR;
	}
	MoveObjectEx(dbObjectID, true);
	SendClientMessageEx(playerID, COLOR_INFO, 470);
	return COMMAND_OK;
}