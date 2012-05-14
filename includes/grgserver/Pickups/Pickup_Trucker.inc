PickupEvent:TRUCKER(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			if (PVar:playerID[JOBID] == JOB_TRUCKER)
			{
				ShowDialog:TRUCKER_OPTIONS(playerID);
			}
			else
			{
				ShowDialog:TRUCKER_JOB(playerID);
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