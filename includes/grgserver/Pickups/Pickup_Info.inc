PickupEvent:INFO(playerID, pickupID, eventType)
{
	if (eventType == PICKUPEVENT_PICKUP)
	{
		MySQLQuery("SELECT * FROM `infopickups` WHERE `pickupId` = '%d'", pickups[pickupID][PICKUP_ID]);
		mysql_store_result();
		new languageStringName[100];
		strcat(languageStringName, GetMySQLField("stringId"));
		mysql_free_result();
		if (StrNotNull(languageStringName))
		{
			SendClientMessageEx(playerID, COLOR_INFO, languageStringName);
			return true;
		}
	}
	return false;
}

PickupModelID:INFO(pickupID)
{
	return 1239;
}