PickupEvent:VEHICLEDEALER(playerID, pickupID)
{
	if (PVar:playerID[JOBID] == JOB_VEHICLEDEALER)
	{
		ShowDialog(playerID, DIALOG_VEHICLEDEALER_OPTIONS);
	}
	else
	{
		ShowDialog(playerID, DIALOG_VEHICLEDEALER_JOB);
	}
}

PickupModelID:VEHICLEDEALER(pickupID)
{
	return 1239;
}