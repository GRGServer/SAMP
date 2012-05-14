PickupEvent:VEHICLEDEALER(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			if (PVar:playerID[JOBID] == JOB_VEHICLEDEALER)
			{
				ShowDialog:VEHICLEDEALER_OPTIONS(playerID);
			}
			else
			{
				ShowDialog:VEHICLEDEALER_JOB(playerID);
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