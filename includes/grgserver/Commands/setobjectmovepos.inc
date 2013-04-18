PCMD:setobjectmovepos[MAPPER](playerID, params[], 463)
{
	if (!PVar:playerID[OBJEDITOR_CURRENTOBJECTID])
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 464);
		return COMMAND_ERROR;
	}

	if (Streamer_GetIntData(STREAMER_TYPE_OBJECT, PVar:playerID[OBJEDITOR_CURRENTOBJECTID], E_STREAMER_EXTRA_ID) != OBJECTTYPE_NORMAL)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 200);
		return COMMAND_ERROR;
	}

	new Float:speed;
	new timeout;
	if (sscanf(params, "fd", speed, timeout))
	{
		if (sscanf(params, "f", speed))
		{
			CmdUsageMsg(playerID, "setobjectmovepos", "Speed", "[Timeout]");
			return COMMAND_USAGE;
		}
	}

	new arrayIndex = PVar:playerID[OBJEDITOR_CURRENTOBJECTID] - 1;
	new Float:position[3];
	new Float:rotation[3];
	GetDynamicObjectPos(PVar:playerID[OBJEDITOR_CURRENTOBJECTID], position[0], position[1], position[2]);
	GetDynamicObjectRot(PVar:playerID[OBJEDITOR_CURRENTOBJECTID], rotation[0], rotation[1], rotation[2]);

	dynamicObjects[arrayIndex][OBJECT_MOVEPOS] = position;
	dynamicObjects[arrayIndex][OBJECT_MOVEROT] = rotation;
	dynamicObjects[arrayIndex][OBJECT_MOVESPEED] = speed;
	dynamicObjects[arrayIndex][OBJECT_MOVETIMEOUT] = timeout;

	SendClientMessageEx(playerID, COLOR_INFO, 465, PVar:playerID[OBJEDITOR_CURRENTOBJECTID]);
	return COMMAND_OK;
}