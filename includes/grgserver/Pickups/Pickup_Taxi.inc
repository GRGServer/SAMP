PickupEvent:TAXI(playerID, pickupID)
{
	ShowDialog(playerID, DIALOG_TAXI);
}

PickupModelID:TAXI(pickupID)
{
	return 1239;
}