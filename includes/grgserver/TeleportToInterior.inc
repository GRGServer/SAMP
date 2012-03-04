TeleportToInterior(playerID, interiorID)
{
	new result;
	MySQLQuery("SELECT * FROM `interiors` WHERE `ID` = '%d'", interiorID);
	mysql_store_result();
	if (strval(GetMySQLField("ID")))
	{
		SetPlayerPos(playerID, floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")));
		SetPlayerFacingAngle(playerID, floatstr(GetMySQLField("Angle")));
		SetPlayerInterior(playerID, strval(GetMySQLField("Interior")));
		result = true;
	}
	mysql_free_result();
	return result;
}