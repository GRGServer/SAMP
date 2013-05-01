PickupEvent:ESTATEAGENTS(playerID, pickupID, eventType)
{
	if (eventType == PICKUPEVENT_KEYPRESS)
	{
		if (PVar:playerID[JOBID] == JOB_ESTATEAGENTS)
		{
			ShowDialog:EstateAgents(playerID);
			return true;
		}
		else
		{
			ShowDialog:EstateAgents_Options(playerID);
		}
	}
	return false;
}

PickupModelID:ESTATEAGENTS(pickupID)
{
	return 1239;
}