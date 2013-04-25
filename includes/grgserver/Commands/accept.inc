CMD:accept(playerID, params[], StringID:94("Accept a job"))
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