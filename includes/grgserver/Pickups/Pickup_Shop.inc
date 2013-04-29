PickupEvent:SHOP(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			ShowDialog:Shop(playerID);
		}
	}
	return false;
}

PickupModelID:SHOP(pickupID)
{
	return 19326;
}