PickupEvent:ESTATEAGENTS(playerID, pickupID, eventType)
{
	if (eventType == PICKUPEVENT_KEYPRESS)
	{
		ShowDialog:ESTATEAGENTS(playerID);
		return true;
	}
	return false;
}

PickupModelID:ESTATEAGENTS(pickupID)
{
	return 1239;
}