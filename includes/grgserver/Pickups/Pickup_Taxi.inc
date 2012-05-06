PickupEvent:TAXI(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			ShowDialog(playerID, DIALOG_TAXI);
			return true;
		}
	}
	return false;
}

PickupModelID:TAXI(pickupID)
{
	return 1210;
}