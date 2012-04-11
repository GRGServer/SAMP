PickupEvent:DRIVINGINSTRUCTOR(playerID, pickupID)
{
	ShowDialog(playerID, DIALOG_SCHOOLDRIVER);
}

PickupModelID:DRIVINGINSTRUCTOR(pickupID)
{
	return 1239;
}