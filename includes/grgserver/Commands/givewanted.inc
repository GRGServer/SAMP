CMD:givewanted(playerID, params[], 557)
{
	if(PVar:playerID[JOBID] == JOB_POLICE)
	{
		new targetPlayerID;
		if (sscanf(params, "u", targetPlayerID))
		{
			ShowDialog:GiveWanted(playerID);
		}
	}
	return COMMAND_PERMISSION_DENIED;
}