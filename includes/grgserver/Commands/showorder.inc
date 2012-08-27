CMD:showorder(playerID, params[], 622)
{
	if (PVar:playerID[JOBID] == JOB_TRUCKER)
	{
		ShowDialog:ShowOrder(playerID);
		return true;
	}
	return COMMAND_PERMISSION_DENIED;
}