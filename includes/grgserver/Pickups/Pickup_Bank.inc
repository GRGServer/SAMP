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
				ShowDialog:Bank_HasAccount(playerID);
			}
			else
			{
				ShowDialog:Bank_NewAccount(playerID);
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