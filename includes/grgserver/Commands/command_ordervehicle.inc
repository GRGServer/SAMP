CMD:ordervehicle(playerid, params[], 113)
{
	if (PVar:playerid[JOBID] == JOB_VEHICLEDEALER)
	{
		ShowDialog(playerid, DIALOG_ORDERVEHICLE);
		return COMMAND_OK;
	}
	return COMMAND_PERMISSION_DENIED;
}