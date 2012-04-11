PickupEvent:AMBULANCE(playerID, pickupID)
{
	ShowDialog(playerID, DIALOG_AMBULANCE);
}

PickupModelID:AMBULANCE(pickupID)
{
	return 1239;
}