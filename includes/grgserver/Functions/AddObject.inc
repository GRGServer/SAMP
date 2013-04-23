AddObject(playerID, modelID, filename[], copyFromCurrent = false)
{
	new Float:position[3];
	new Float:rotation[3];
	new interior = GetPlayerInterior(playerID);

	if (copyFromCurrent)
	{
		GetDynamicObjectPos(PVar:playerID[OBJEDITOR_CURRENTOBJECTID], position[0], position[1], position[2]);
		GetDynamicObjectRot(PVar:playerID[OBJEDITOR_CURRENTOBJECTID], rotation[0], rotation[1], rotation[2]);
	}
	else
	{
		GetPlayerPos(playerID, position[0], position[1], position[2]);
	}

	new objectID = CreateDynamicObject(modelID, position[0], position[1], position[2], rotation[0], rotation[1], rotation[2], -1, interior, -1, STREAMER_OBJECTDISTANCE);
	Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID, OBJECTTYPE_NORMAL);

	format(dynamicObjects[objectID - 1][OBJECT_FILENAME], STRINGLENGTH_OBJECTFILENAME, "%s", filename);
	dynamicObjects[objectID - 1][OBJECT_ID] = nextDynamicObjectID;
	dynamicObjects[objectID - 1][OBJECT_POS] = position;
	dynamicObjects[objectID - 1][OBJECT_ROT] = rotation;

	nextDynamicObjectID++;

	UpdateObjectsForAllPlayers();

	PlaySound(playerID, SOUND_OBJECTPLACED);
	SendClientMessageEx(playerID, COLOR_INFO, StringID:396(""), dynamicObjects[objectID - 1][OBJECT_ID], objectModels[modelID]);

	OnPlayerSelectDynamicObject(playerID, objectID, modelID, position[0], position[1], position[2]);

	return objectID;
}