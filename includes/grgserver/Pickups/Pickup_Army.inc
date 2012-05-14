PickupEvent:ARMY(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			ShowDialog:ARMY(playerID);
			return true;
		}
	}
	return false;
}

PickupModelID:ARMY(pickupID)
{
	return 1210;
}