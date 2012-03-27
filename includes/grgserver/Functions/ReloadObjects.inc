ReloadObjects()
{
	printf("* Loading objects...");
	DestroyAllDynamicObjects();
	MySQLQuery("SELECT * FROM `objects`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		CreateDynamicObject(strval(GetMySQLField("ModelID")), floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")), floatstr(GetMySQLField("RotX")), floatstr(GetMySQLField("RotY")), floatstr(GetMySQLField("RotZ")), -1, strval(GetMySQLField("Interior")), -1, 100.0);
	}
	mysql_free_result();
}