PickupEvent:AMBULANCE(playerID, pickupID, eventType)
{
	if (eventType == PICKUPEVENT_KEYPRESS)
	{
		ShowDialog:Ambulance(playerID);
	}
}

PickupModelID:AMBULANCE(pickupID)
{
	return 1240;
}