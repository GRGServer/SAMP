PickupEvent:TAXI(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			ShowDialog:TAXI(playerID);
			return true;
		}
	}
	return false;
}

PickupModelID:TAXI(pickupID)
{
	return 1210;
}