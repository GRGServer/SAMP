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
		new objectID = CreateDynamicObject(strval(GetMySQLField("ModelID")), floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")), floatstr(GetMySQLField("RotX")), floatstr(GetMySQLField("RotY")), floatstr(GetMySQLField("RotZ")), -1, strval(GetMySQLField("Interior")), -1, 100.0);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID, strval(GetMySQLField("ID")));
		count++;
	}
	mysql_free_result();
	AdminPrint(playerID, COLOR_INFO, "  %d objects loaded", count);
}