CMD:taz(playerID, params[], 555)
{
	if(PVar:playerID[JOBID] == JOB_POLICE)
	{
		new targetplayerID;
		TogglePlayerControllable(targetplayerID, false);
		return COMMAND_OK;
	}
	return COMMAND_PERMISSION_DENIED;
}