CheckGatePermission(playerID, gateObjectID)
{
	switch (gateObjectID)
	{
		case 310:// Los Santos Police Department area
		{
			if (PVar:playerID[JOBID] != JOB_POLICE)
			{
				return false;
			}
		}
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
		case 1691:// Los Santos Police Department garage
		{
			if (PVar:playerID[JOBID] != JOB_POLICE)
			{
				return false;
			}
		}
		case 1766:// Los Santos Airport gate
		{
			return true;// TODO: Currently allowed for all players (Need job?)
		}
	}
	return true;// Set default to let the player enter this area
}