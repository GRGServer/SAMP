CMD:givewanted(playerID, params[], StringID:560("Set the wanted level of a player"))
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
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:558("Level must be between 0 and 6!"));
			return COMMAND_ERROR;
		}
		SetPlayerWantedLevel(targetPlayerID, level);
		SendClientMessageEx(playerID, COLOR_INFO, StringID:559("The wanted level of %p has been set to %d"), targetPlayerID, level);
		return COMMAND_OK;
	}
	return COMMAND_PERMISSION_DENIED;
}