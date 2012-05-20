PickupEvent:HOSPITAL(playerID, pickupID, eventType)
{
	if (eventType == PICKUPEVENT_KEYPRESS)
	{
		ShowDialog:Hospital(playerID);
	}
}

PickupModelID:HOSPITAL(pickupID)
{
	return 1240;
}