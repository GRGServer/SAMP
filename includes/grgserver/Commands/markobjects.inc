PCMD:markobjects[MAPPER](playerID, params[], StringID:482("Mark up to 100 objects on your map"))
{
	new modelID;
	if (sscanf(params, "d", modelID))
	{
		CmdUsageMsg(playerID, "markobjects", "ModelID");
		return COMMAND_USAGE;
	}

	new count;
	new dynamicObjectsCount = CountDynamicObjects();
	new Float:foundObjects[100][3];
	Count(arrayIndex, dynamicObjectsCount)
	{
		if (Streamer_GetIntData(STREAMER_TYPE_OBJECT, arrayIndex + 1, E_STREAMER_MODEL_ID) == modelID)
		{
			foundObjects[count][0] = dynamicObjects[arrayIndex][OBJECT_POS][0];
			foundObjects[count][1] = dynamicObjects[arrayIndex][OBJECT_POS][1];
			foundObjects[count][2] = dynamicObjects[arrayIndex][OBJECT_POS][2];
			count++;
			if (count >= 100)
			{
				break;
			}
		}
	}

	if (count)
	{
		Count(iconID, 100)
		{
			RemovePlayerMapIcon(playerID, iconID);
		}

		Count(iconID, count)
		{
			SetPlayerMapIcon(playerID, iconID, foundObjects[iconID][0], foundObjects[iconID][1], foundObjects[iconID][2], 0, COLOR_MARKER_OBJECT, MAPICON_GLOBAL);
		}

		return COMMAND_OK;
	}

	SendClientMessageEx(playerID, COLOR_ERROR, StringID:425("No object found!"));
	return COMMAND_ERROR;
}