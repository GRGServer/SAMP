PickupEvent:ARMY(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			if (PVar:playerID[JOBID] == JOB_ARMEE)
			{
				ShowDialog:Army(playerID);
				return true;
			}
			else
			{
				ShowDialog:Army_Options(playerID);
			}
		}
	}
	return false;
}

PickupModelID:ARMY(pickupID)
{
	return 1210;
}