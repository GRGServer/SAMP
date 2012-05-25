PickupEvent:TRUCKER(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			if (PVar:playerID[JOBID] == JOB_TRUCKER)
			{
				//ShowDialog:Trucker_Options(playerID);// TODO: Recreate dialogs
			}
			else
			{
				//ShowDialog:Trucker_Job(playerID);// TODO: Recreate dialogs
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