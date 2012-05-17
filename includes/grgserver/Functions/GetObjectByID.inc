GetObjectByID(objectID)
{
	new objects = CountDynamicObjects();
	Count1(id, objects)
	{
		if (Streamer_GetIntData(STREAMER_TYPE_OBJECT, id, E_STREAMER_EXTRA_ID) == objectID)
		{
			return id;
		}
	}
	return 0;
}