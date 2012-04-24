PickupEvent:POLICE(playerID, pickupID)
{
	if (PVar:playerID[JOBID] == JOB_POLICE)
	{
		ShowDialog(playerID, DIALOG_POLICE_OPTIONS);
	}
	else
	{
		ShowDialog(playerID, DIALOG_POLICE_JOB);
	}
}

PickupModelID:POLICE(pickupID)
{
	return 1247;
}