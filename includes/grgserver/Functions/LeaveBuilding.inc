LeaveBuilding(playerID)
{
	new CurrentBuildingID = PVar:playerID[CURRENTBUILDINGID];
	if (CurrentBuildingID)
	{
		MySQLQuery("SELECT `PosX`, `PosY`, `PosZ` FROM `pickups` WHERE `ID` = '%d'", strval(GetMySQLValue("buildings", "PickupID", "ID", val2str(CurrentBuildingID))));
		mysql_store_result();
		SetPlayerPos(playerID, floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")));
		SetPlayerInterior(playerID, 0);
		SetPlayerVirtualWorld(playerID, 0);
		PVar:playerID[CURRENTBUILDINGID] = 0;
		mysql_free_result();
		return true;
	}
	return false;
}