LeaveProperty(playerID)
{
	if (PVar:playerID[CURRENTPROPERTYID])
	{
		MySQLQuery("SELECT `posX`, `posY`, `posZ` FROM `properties` LEFT JOIN `pickups` ON `pickups`.`id` = `properties`.`pickupId` WHERE `properties`.`id` = '%d'", PVar:playerID[CURRENTPROPERTYID]);
		mysql_store_result();
		SetPlayerPosEx(playerID, floatstr(GetMySQLField("posX")), floatstr(GetMySQLField("posY")), floatstr(GetMySQLField("posZ")));
		SetPlayerInterior(playerID, 0);
		SetPlayerVirtualWorld(playerID, 0);
		PVar:playerID[CURRENTPROPERTYID] = 0;
		mysql_free_result();
		return true;
	}
	return false;
}