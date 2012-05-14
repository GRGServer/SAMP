PickupEvent:BANK(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			TeleportToProperty(playerID, strval(GetMySQLValue("properties", "ID", "PickupID", val2str(pickups[pickupID][PICKUP_ID]))));
			new bankID = strval(GetUserDBValue(playerID, "BankID"));
			if (bankID)
			{
				ShowDialog:BANK_HASACCOUNT(playerID);
			}
			else
			{
				ShowDialog:BANK_NEWACCOUNT(playerID);
			}
			return true;
		}
	}
	return false;
}

PickupModelID:BANK(pickupID)
{
	return 1274;
}