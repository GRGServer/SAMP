/**
 * <summary>
 *	Called once a dynamic object stops moving.
 * </summary>
 *
 * <param name="objectid">
 *	The ID of the object which stopped moving.
 * </param>
 *
 * <remarks>
 *	The timer MoveObject gets called if there is an entry for the object in the <b>movedobjects</b> table and a timeout is defined.
 * </remarks>
 */

public OnDynamicObjectMoved(objectid)
{
	new dbObjectID = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID);
	if (dbObjectID <= 0)
	{
		return true;
	}
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:rotX;
	new Float:rotY;
	new Float:rotZ;
	GetDynamicObjectPos(objectid, posX, posY, posZ);
	GetDynamicObjectRot(objectid, rotX, rotY, rotZ);
	MySQLQuery("SELECT * FROM `moveobjects` WHERE `ObjectID` = '%d'", dbObjectID);
	mysql_store_result();
	new Float:movedPosX = floatstr(GetMySQLField("PosX"));
	new Float:movedPosY = floatstr(GetMySQLField("PosY"));
	new Float:movedPosZ = floatstr(GetMySQLField("PosZ"));
	new Float:movedRotX = floatstr(GetMySQLField("RotX"));
	new Float:movedRotY = floatstr(GetMySQLField("RotY"));
	new Float:movedRotZ = floatstr(GetMySQLField("RotZ"));
	new timeout = strval(GetMySQLField("Timeout"));
	mysql_free_result();
	if (timeout && movedPosX == posX && movedPosY == posY && movedPosZ == posZ && movedRotX == rotX && movedRotY == rotY && movedRotZ == rotZ)
	{
		SetTimerEx("Timer_MoveObject", timeout, false, "dd", dbObjectID, false);
	}
	return true;
}