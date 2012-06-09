ReloadObjects(playerID = INVALID_PLAYER_ID)
{
	AdminPrint(playerID, COLOR_INFO, "* Destroying objects...");
	DestroyAllDynamicObjects();
	AdminPrint(playerID, COLOR_INFO, "* Loading objects...");
	new count;
	MySQLQuery("SELECT * FROM `objects`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new objectID = CreateDynamicObject(strval(GetMySQLField("modelId")), floatstr(GetMySQLField("posX")), floatstr(GetMySQLField("posY")), floatstr(GetMySQLField("posZ")), floatstr(GetMySQLField("rotX")), floatstr(GetMySQLField("rotY")), floatstr(GetMySQLField("rotZ")), -1, strval(GetMySQLField("interior")), -1, STREAMER_OBJECTDISTANCE);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID, strval(GetMySQLField("id")));
		count++;
	}
	mysql_free_result();
	UpdateObjectsForAllPlayers();
	AdminPrint(playerID, COLOR_INFO, "  %d objects loaded", count);
}