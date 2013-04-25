CMD:opengate(playerID, params[], StringID:467("Open a gate or door"))
{
	new Float:distance;
	new objectID = GetClosestGate(playerID, distance);
	if (!objectID || distance > 15)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:468("There is no gate which can be opened!"));
		return COMMAND_ERROR;
	}

	if (!CheckGatePermission(playerID, objectID))
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:469("You do not have the permission to open this gate!"));
		return COMMAND_ERROR;
	}

	MoveObjectEx(objectID, true);

	SendClientMessageEx(playerID, COLOR_INFO, StringID:470("The gate will now open"));
	return COMMAND_OK;
}