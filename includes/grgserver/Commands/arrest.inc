CMD:arrest(playerID, params[], 554)
{
	if(PVar:playerID[JOBID] == JOB_POLICE)
	{
		return COMMAND_OK;
	}
	return COMMAND_PERMISSION_DENIED;
}
