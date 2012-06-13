CheckGatePermission(playerID, gateObjectID)
{
	switch (gateObjectID)
	{
		case 1647:// Las Venturas ADAC vehicle area
		{
			if (PVar:playerID[JOBID] != JOB_ADAC)
			{
				return false;
			}
		}
		case 1686:// Las Venturas trucker area
		{
			if (PVar:playerID[JOBID] != JOB_TRUCKER)
			{
				return false;
			}
		}
	}
	return true;// Set default to let the player enter this area
}