PickupEvent:ADAC(playerID, pickupID, eventType)
{
	if (eventType == PICKUPEVENT_KEYPRESS)
	{
		if (PVar:playerID[JOBID] == JOB_ADAC)
		{
			ShowDialog:ADAC(playerID);
		}
		else
		{
			ShowDialog:ADAC_Options(playerID);
		}
	}
}

PickupModelID:ADAC(pickupID)
{
	return 1210;
}