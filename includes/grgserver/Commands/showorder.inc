CMD:showorder(playerID, params[], StringID:622("Show current orders"))
{
	if (PVar:playerID[JOBID] == JOB_TRUCKER)
	{
		ShowDialog:ShowOrder(playerID);
		return true;
	}
	return COMMAND_PERMISSION_DENIED;
}