PickupEvent:ESTATEAGENTS(playerID, pickupID, eventType)
{
	if (eventType == PICKUPEVENT_KEYPRESS)
	{
		ShowDialog(playerID, DIALOG_ESTATEAGENTS);
		return true;
	}
	return false;
}

PickupModelID:ESTATEAGENTS(pickupID)
{
	return 1239;
}