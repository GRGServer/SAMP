ReloadPickup(pickupID)
{
	Count(internalPickupID, MAX_PICKUPS)
	{
		if (pickups[internalPickupID][PICKUP_ID] == pickupID)
		{
			DestroyPickup(internalPickupID);
			pickups[internalPickupID][PICKUP_ID] = 0;
			pickups[internalPickupID][PICKUP_TYPE] = 0;
			break;
		}
	}
	MySQLQuery("SELECT * FROM `pickups` WHERE `id` = '%d'", pickupID);
	mysql_store_result();
	if (!AddPickup(strval(GetMySQLField("id")), GetMySQLField("type"), floatstr(GetMySQLField("posX")), floatstr(GetMySQLField("posY")), floatstr(GetMySQLField("posZ"))))
	{
		printf("Invalid pickup type: %s", GetMySQLField("type"));
	}
	mysql_free_result();
}