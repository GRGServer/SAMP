CMD:missions(playerID, params[], StringID:94("Show available missions"))
{
	if (!PVar:playerID[JOBID])
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:33("You do not have a job!"));
		return COMMAND_ERROR;
	}

	ShowDialog:Missions(playerID);
	return COMMAND_OK;
}