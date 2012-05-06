PickupEvent:AMBULANCE(playerID, pickupID, eventType)
{
	if (eventType == PICKUPEVENT_KEYPRESS)
	{
		ShowDialog(playerID, DIALOG_AMBULANCE);
	}
}

PickupModelID:AMBULANCE(pickupID)
{
	return 1240;
}