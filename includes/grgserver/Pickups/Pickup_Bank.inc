PickupEvent:BANK(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			TeleportToInterior(playerID, 85);
			PVar:playerID[CURRENTPROPERTYID] = strval(GetMySQLValue("properties", "id", "pickupId", val2str(pickups[pickupID][PICKUP_ID])));
			SetPlayerVirtualWorld(playerID, PVar:playerID[CURRENTPROPERTYID]);
			if (PVar:playerID[BANK_ID])
			{
				ShowDialog:Bank_PIN(playerID);
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