GetClosestNavigationLocation(playerID, typeID, &Float:posX, &Float:posY, &Float:posZ)
{
	new found;
	new Float:oldDistance = 6000.0;
	MySQLQuery("SELECT * FROM `navigationlocations` WHERE `type` = '%d'", typeID);
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new Float:distance = GetPlayerDistanceFromPoint(playerID, floatstr(GetMySQLField("posX")), floatstr(GetMySQLField("posY")), floatstr(GetMySQLField("posZ")));
		if (distance < oldDistance)
		{
			oldDistance = distance;
			posX = floatstr(GetMySQLField("posX"));
			posY = floatstr(GetMySQLField("posY"));
			posZ = floatstr(GetMySQLField("posZ"));
			found = true;
		}
	}
	mysql_free_result();
	return found;
}