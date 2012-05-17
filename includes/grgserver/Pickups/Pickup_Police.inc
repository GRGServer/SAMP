PickupEvent:POLICE(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			if (PVar:playerID[JOBID] == JOB_POLICE)
			{
				ShowDialog:Police_Options(playerID);
			}
			else
			{
				ShowDialog:Police_Job(playerID);
			}
			return true;
		}
	}
	return false;
}

PickupModelID:POLICE(pickupID)
{
	return 1247;
}