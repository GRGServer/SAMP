CMD:opengate(playerID, params[], StringID:467(""))
{
	new Float:distance;
	new objectID = GetClosestGate(playerID, distance);
	if (!objectID || distance > 15)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:468(""));
		return COMMAND_ERROR;
	}

	if (!CheckGatePermission(playerID, objectID))
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:469(""));
		return COMMAND_ERROR;
	}

	MoveObjectEx(objectID, true);

	SendClientMessageEx(playerID, COLOR_INFO, StringID:470(""));
	return COMMAND_OK;
}