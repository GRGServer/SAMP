ReloadPickup(pickupID)
{
	for (new internalPickupID = 0; internalPickupID < MAX_PICKUPS; internalPickupID++)
	{
		if (pickups[internalPickupID][PICKUP_ID] == pickupID)
		{
			DestroyPickup(internalPickupID);
			pickups[internalPickupID][PICKUP_ID] = 0;
			pickups[internalPickupID][PICKUP_TYPE] = 0;
			break;
		}
	}
	MySQLQuery("SELECT * FROM `pickups` WHERE `ID` = '%d'", pickupID);
	mysql_store_result();
	if (AddPickup(strval(GetMySQLField("ID")), GetMySQLField("Type"), floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")), false) == -1)
	{
		printf("Invalid pickup type: %s", GetMySQLField("Type"));
	}
	mysql_free_result();
}