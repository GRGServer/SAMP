MoveObjectEx(dbObjectID, newState)
{
	new rows;
	MySQLQuery("SELECT * FROM `objects` WHERE `id` = '%d'", dbObjectID);
	mysql_store_result();
	rows = mysql_num_rows();
	new Float:normalPosX = floatstr(GetMySQLField("posX"));
	new Float:normalPosY = floatstr(GetMySQLField("posY"));
	new Float:normalPosZ = floatstr(GetMySQLField("posZ"));
	new Float:normalRotX = floatstr(GetMySQLField("rotX"));
	new Float:normalRotY = floatstr(GetMySQLField("rotY"));
	new Float:normalRotZ = floatstr(GetMySQLField("rotZ"));
	mysql_free_result();
	if (!rows)
	{
		return -1;
	}
	MySQLQuery("SELECT * FROM `moveobjects` WHERE `objectId` = '%d'", dbObjectID);
	mysql_store_result();
	rows = mysql_num_rows();
	new Float:movedPosX = floatstr(GetMySQLField("posX"));
	new Float:movedPosY = floatstr(GetMySQLField("posY"));
	new Float:movedPosZ = floatstr(GetMySQLField("posZ"));
	new Float:movedRotX = floatstr(GetMySQLField("rotX"));
	new Float:movedRotY = floatstr(GetMySQLField("rotY"));
	new Float:movedRotZ = floatstr(GetMySQLField("rotZ"));
	new Float:speed = floatstr(GetMySQLField("speed"));
	mysql_free_result();
	if (!rows)
	{
		return -2;
	}
	new objectID = GetObjectByID(dbObjectID);
	if (!objectID)
	{
		return false;
	}
	StopDynamicObject(objectID);
	if (newState)
	{
		MoveDynamicObject(objectID, movedPosX, movedPosY, movedPosZ, speed, movedRotX, movedRotY, movedRotZ);
	}
	else
	{
		MoveDynamicObject(objectID, normalPosX, normalPosY, normalPosZ, speed, normalRotX, normalRotY, normalRotZ);
	}
	return true;
}