LeaveProperty(playerID)
{
	new CurrentPropertyID = PVar:playerID[CURRENTPROPERTYID];
	if (CurrentPropertyID)
	{
		MySQLQuery("SELECT `PosX`, `PosY`, `PosZ` FROM `pickups` WHERE `ID` = '%d'", strval(GetMySQLValue("properties", "PickupID", "ID", val2str(CurrentPropertyID))));
		mysql_store_result();
		SetPlayerPosEx(playerID, floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")));
		SetPlayerInterior(playerID, 0);
		SetPlayerVirtualWorld(playerID, 0);
		PVar:playerID[CURRENTPROPERTYID] = 0;
		mysql_free_result();
		return true;
	}
	return false;
}