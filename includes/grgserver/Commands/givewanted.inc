CMD:givewanted(playerID, params[], 560)
{
	if (PVar:playerID[JOBID] == JOB_POLICE || PVar:playerID[JOBID] == JOB_GOVERMENT || PVar:playerID[JOBID] == JOB_ARMEE)
	{
		new targetPlayerID;
		new level;
		if (sscanf(params, "ud", targetPlayerID, level))
		{
			CmdUsageMsg(playerID, "givewanted", "PlayerID/Name", "Level");
			return COMMAND_USAGE;
		}
		if (targetPlayerID == INVALID_PLAYER_ID)
		{
			return COMMAND_PLAYER_NOT_FOUND;
		}
		if (level < 0 || level > 6)
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 558);
			return COMMAND_ERROR;
		}
		SetPlayerWantedLevel(targetPlayerID, level);
		SendClientMessageEx(playerID, COLOR_INFO, 559, targetPlayerID, level);
		return COMMAND_OK;
	}
	return COMMAND_PERMISSION_DENIED;
}