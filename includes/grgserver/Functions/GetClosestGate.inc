GetClosestGate(playerID, &Float:closestObjectDistance)
{
	new closestObjectID;
	new objects = CountDynamicObjects();
	Count1(objectID, objects)
	{
		if (IsGateObject(Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_MODEL_ID)))
		{
			new Float:posX;
			new Float:posY;
			new Float:posZ;
			Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_X, posX);
			Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_Y, posY);
			Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_Z, posZ);
			new Float:distance = GetPlayerDistanceFromPoint(playerID, posX, posY, posZ);
			if (distance < closestObjectDistance || !closestObjectID)
			{
				closestObjectID = objectID;
				closestObjectDistance = distance;
			}
		}
	}
	return closestObjectID;
}