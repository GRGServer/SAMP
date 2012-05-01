PickupEvent:BANK(playerID, pickupID)
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
}

PickupModelID:BANK(pickupID)
{
	return 1274;
}