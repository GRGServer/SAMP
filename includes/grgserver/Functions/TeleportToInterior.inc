TeleportToInterior(playerID, interiorID)
{
	new result;
	MySQLQuery("SELECT * FROM `interiors` WHERE `id` = '%d'", interiorID);
	mysql_store_result();
	if (strval(GetMySQLField("id")))
	{
		SetPlayerPosEx(playerID, floatstr(GetMySQLField("posX")), floatstr(GetMySQLField("posY")), floatstr(GetMySQLField("posZ")));
		SetPlayerFacingAngle(playerID, floatstr(GetMySQLField("angle")));
		SetPlayerInterior(playerID, strval(GetMySQLField("interior")));
		PVar:playerID[CURRENTINTERIOR] = interiorID;
		result = true;
	}
	mysql_free_result();
	return result;
}