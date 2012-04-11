PickupEvent:TRUCKER(playerID, pickupID)
{
	if (PVar:playerID[JOBID] == JOB_TRUCKER)
	{
		ShowDialog(playerID, DIALOG_TRUCKER_OPTIONS);
	}
	else
	{
		ShowDialog(playerID, DIALOG_TRUCKER_JOB);
	}
}

PickupModelID:TRUCKER(pickupID)
{
	return 1239;
}