GetObjectByID(objectID)
{
	for (new id = 1; id < objects; id++)
	{
		if (Streamer_GetIntData(STREAMER_TYPE_OBJECT, id, E_STREAMER_EXTRA_ID) == objectID)
		{
			return id;
		}
	}
	return 0;
}