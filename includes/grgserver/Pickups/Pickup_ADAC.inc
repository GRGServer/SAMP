PickupEvent:ADAC(playerID, pickupID, eventType)
{
	if (eventType == PICKUPEVENT_KEYPRESS)
	{
		ShowDialog(playerID, DIALOG_ADAC);
	}
}

PickupModelID:ADAC(pickupID)
{
	return 1210;
}