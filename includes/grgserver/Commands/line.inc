CMD:line(playerID, params[], 561)
{
	if (PVar:playerID[JOBID] != JOB_BUSDRIVER)
	{
		return COMMAND_PERMISSION_DENIED;
	}
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!vehicleID)
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	new modelID = GetVehicleModel(vehicleID);
	if (modelID == 431 || modelID == 437)
	{
		ShowDialog:BusLine(playerID);
		return COMMAND_OK;
	}
	SendClientMessageEx(playerID, COLOR_ERROR, "563");
	return COMMAND_ERROR;
}