CMD:line(playerID, params[], StringID:561("Change bus line"))
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
	SendClientMessageEx(playerID, COLOR_ERROR, StringID:563("You are not driving a bus!"));
	return COMMAND_ERROR;
}