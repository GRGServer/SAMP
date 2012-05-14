PickupEvent:ADAC(playerID, pickupID, eventType)
{
	if (eventType == PICKUPEVENT_KEYPRESS)
	{
		ShowDialog:ADAC(playerID);
	}
}

PickupModelID:ADAC(pickupID)
{
	return 1210;
}