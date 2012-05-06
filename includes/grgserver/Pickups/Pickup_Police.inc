PickupEvent:POLICE(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			if (PVar:playerID[JOBID] == JOB_POLICE)
			{
				ShowDialog(playerID, DIALOG_POLICE_OPTIONS);
			}
			else
			{
				ShowDialog(playerID, DIALOG_POLICE_JOB);
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