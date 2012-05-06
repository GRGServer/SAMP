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
				ShowDialog(playerID, DIALOG_BANK_HASACCOUNT);
			}
			else
			{
				ShowDialog(playerID, DIALOG_BANK_NEWACCOUNT);
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