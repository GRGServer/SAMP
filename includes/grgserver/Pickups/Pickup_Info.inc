PickupEvent:INFO(playerID, pickupID, eventType)
{
	if (eventType == PICKUPEVENT_PICKUP)
	{
		MySQLQuery("SELECT * FROM `infopickups` WHERE `pickupId` = '%d'", pickups[pickupID][PICKUP_ID]);
		mysql_store_result();
		new stringID = strval(GetMySQLField("stringId"));
		mysql_free_result();
		if (stringID)
		{
			SendClientMessageEx(playerID, COLOR_INFO, stringID);
			return true;
		}
	}
	return false;
}

PickupModelID:INFO(pickupID)
{
	return 1239;
}