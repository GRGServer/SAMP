MoveObjectEx(dbObjectID, newState)
{
	new rows;
	MySQLQuery("SELECT * FROM `objects` WHERE `ID` = '%d'", dbObjectID);
	mysql_store_result();
	rows = mysql_num_rows();
	new Float:normalPosX = floatstr(GetMySQLField("PosX"));
	new Float:normalPosY = floatstr(GetMySQLField("PosY"));
	new Float:normalPosZ = floatstr(GetMySQLField("PosZ"));
	new Float:normalRotX = floatstr(GetMySQLField("RotX"));
	new Float:normalRotY = floatstr(GetMySQLField("RotY"));
	new Float:normalRotZ = floatstr(GetMySQLField("RotZ"));
	mysql_free_result();
	if (!rows)
	{
		return -1;
	}
	MySQLQuery("SELECT * FROM `moveobjects` WHERE `ObjectID` = '%d'", dbObjectID);
	mysql_store_result();
	rows = mysql_num_rows();
	new Float:movedPosX = floatstr(GetMySQLField("PosX"));
	new Float:movedPosY = floatstr(GetMySQLField("PosY"));
	new Float:movedPosZ = floatstr(GetMySQLField("PosZ"));
	new Float:movedRotX = floatstr(GetMySQLField("RotX"));
	new Float:movedRotY = floatstr(GetMySQLField("RotY"));
	new Float:movedRotZ = floatstr(GetMySQLField("RotZ"));
	new Float:speed = floatstr(GetMySQLField("Speed"));
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