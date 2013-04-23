PCMD:moveobjects[MAPPER](playerID, params[], StringID:636(""))
{
	new fileName[STRINGLENGTH_OBJECTFILENAME];
	new Float:x;
	new Float:y;
	new Float:z;

	if (sscanf(params, "s[" #STRINGLENGTH_OBJECTFILENAME "]fff", fileName, x, y, z))
	{
		CmdUsageMsg(playerID, "moveobjects", LanguageString(playerID, StringID:634("")), "X", "Y", "Z");
		return COMMAND_USAGE;
	}

	new count;
	Foreach(arrayIndex, dynamicObjects)
	{
		if (!strcmp(dynamicObjects[arrayIndex][OBJECT_FILENAME], fileName, true))
		{
			dynamicObjects[arrayIndex][OBJECT_POS][0] = dynamicObjects[arrayIndex][OBJECT_POS][0] + x;
			dynamicObjects[arrayIndex][OBJECT_POS][1] = dynamicObjects[arrayIndex][OBJECT_POS][1] + y;
			dynamicObjects[arrayIndex][OBJECT_POS][2] = dynamicObjects[arrayIndex][OBJECT_POS][2] + z;
			SetDynamicObjectPos(arrayIndex + 1, dynamicObjects[arrayIndex][OBJECT_POS][0], dynamicObjects[arrayIndex][OBJECT_POS][1], dynamicObjects[arrayIndex][OBJECT_POS][2]);
			count++;
		}
	}

	UpdateObjectsForAllPlayers();

	SendClientMessageEx(playerID, COLOR_INFO, StringID:635(""), count);
	return COMMAND_OK;
}