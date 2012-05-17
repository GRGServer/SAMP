PickupEvent:TAXI(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			ShowDialog:Taxi(playerID);
			return true;
		}
	}
	return false;
}

PickupModelID:TAXI(pickupID)
{
	return 1210;
}