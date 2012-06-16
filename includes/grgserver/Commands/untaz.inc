CMD:untaz(playerID, params[], 556)
{
	if(PVar:playerID[JOBID] == JOB_POLICE)
	{
		new targetPlayerID;
		TogglePlayerControllable(targetPlayerID, true);
		return COMMAND_OK;
	}
	return COMMAND_PERMISSION_DENIED;
}