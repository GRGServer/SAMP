CMD:showorder(playerID, params[],)
{
	if (PVar:playerID[JOBID] == JOB_TRUCKER)
	{
		ShowDialog:ShowOrder(playerID);
		return true;
	}
	return COMMAND_PERMISSION_DENIED;
}