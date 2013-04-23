PCMD:moveobject[MAPPER](playerID, params[], StringID:0(""))
{
	new objectID;
	new direction;
	if (sscanf(params, "dd", objectID, direction))
	{
		CmdUsageMsg(playerID, "moveobject", "ObjectID", "Direction");
		return COMMAND_USAGE;
	}
	switch (MoveObjectEx(objectID, direction))
	{
		case -2:
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:466(""));
			return COMMAND_ERROR;
		}
		case -1:
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:427(""));
			return COMMAND_ERROR;
		}
		case true:
		{
			return COMMAND_OK;
		}
	}
	return COMMAND_ERROR;
}