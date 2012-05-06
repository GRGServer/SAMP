PickupEvent:TRUCKER(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			if (PVar:playerID[JOBID] == JOB_TRUCKER)
			{
				ShowDialog(playerID, DIALOG_TRUCKER_OPTIONS);
			}
			else
			{
				ShowDialog(playerID, DIALOG_TRUCKER_JOB);
			}
			return true;
		}
	}
	return false;
}

PickupModelID:TRUCKER(pickupID)
{
	return 1239;
}