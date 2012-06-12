CMD:givelicense(playerID, params[], 511)
{
	new targetPlayerID;
	if (sscanf(params, "u", targetPlayerID))
	{
		CmdUsageMsg(playerID, "givelicense", "PlayerID/Name");
		return COMMAND_USAGE;
	}
	if(PVar:playerID[JOBID] == JOB_SCHOOLDRIVER)
	{
		if(PVar:playerID[LICENSEID] == LICENSE_VEHICLE)
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 512);
		}
		else
		{
			MySQLQuery("UPDATE `users` SET `licenseId` = '1' WHERE `id` = '%d'",PVar:targetPlayerID[USERID]);
			SendClientMessageEx(playerID, COLOR_INFO, 513);
		}
	}
	return COMMAND_OK;
}