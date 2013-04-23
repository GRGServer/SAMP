CMD:ordervehicle(playerID, params[], StringID:113(""))
{
	if (PVar:playerID[JOBID] == JOB_VEHICLEDEALER)
	{
		ShowDialog:OrderVehicle(playerID);
		return COMMAND_OK;
	}
	return COMMAND_PERMISSION_DENIED;
}