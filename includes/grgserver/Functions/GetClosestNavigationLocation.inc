GetClosestNavigationLocation(playerID, typeID, &Float:posX, &Float:posY, &Float:posZ)
{
	new found;
	new Float:oldDistance = 6000.0;
	MySQLQuery("SELECT * FROM `navigationlocations` WHERE `Type` = '%d'", typeID);
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new Float:distance = GetPlayerDistanceFromPoint(playerID, floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")));
		if (distance < oldDistance)
		{
			oldDistance = distance;
			posX = floatstr(GetMySQLField("PosX"));
			posY = floatstr(GetMySQLField("PosY"));
			posZ = floatstr(GetMySQLField("PosZ"));
			found = true;
		}
	}
	mysql_free_result();
	return found;
}