CMD:accept(playerID, params[], 94)
{
	switch (PVar:playerID[JOBID])
	{
		case JOB_TAXI, JOB_ADAC, JOB_PARAMEDIC, JOB_POLICE, JOB_TRUCKER:
		{
			ShowDialog:Accept(playerID);
		}
		default:
		{
			return COMMAND_PERMISSION_DENIED;
		}
	}
	return COMMAND_OK;
}