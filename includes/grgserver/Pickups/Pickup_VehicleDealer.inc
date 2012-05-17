PickupEvent:VEHICLEDEALER(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			if (PVar:playerID[JOBID] == JOB_VEHICLEDEALER)
			{
				ShowDialog:VehicleDealer_Options(playerID);
			}
			else
			{
				ShowDialog:VehicleDealer_Job(playerID);
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