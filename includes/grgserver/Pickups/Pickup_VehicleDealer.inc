PickupEvent:VEHICLEDEALER(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			if (PVar:playerID[JOBID] == JOB_VEHICLEDEALER)
			{
				ShowDialog(playerID, DIALOG_VEHICLEDEALER_OPTIONS);
			}
			else
			{
				ShowDialog(playerID, DIALOG_VEHICLEDEALER_JOB);
			}
			return true;
		}
	}
	return false;
}

PickupModelID:VEHICLEDEALER(pickupID)
{
	return 1239;
}