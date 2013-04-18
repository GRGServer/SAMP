GetClosestGate(playerID, &Float:closestObjectDistance)
{
	new closestObjectID;
	new objects = CountDynamicObjects();

	Count1(objectID, objects)
	{
		if (IsValidDynamicObject(objectID) && IsGateObject(Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_MODEL_ID)))
		{
			new Float:position[3];
			Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_X, position[0]);
			Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_Y, position[1]);
			Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_Z, position[2]);
			new Float:distance = GetPlayerDistanceFromPoint(playerID, position[0], position[1], position[2]);

			if ((distance < closestObjectDistance || !closestObjectID) && dynamicObjects[objectID - 1][OBJECT_MOVESPEED])// This distance is lower than the last one and move speed has been defined
			{
				closestObjectID = objectID;
				closestObjectDistance = distance;
			}
		}
	}

	return closestObjectID;
}