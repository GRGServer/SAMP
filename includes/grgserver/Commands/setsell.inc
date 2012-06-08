CMD:setsell(playerID, params[], 495)
{
	if (PVar:playerID[JOBID] != JOB_VEHICLEDEALER)
	{
		return COMMAND_PERMISSION_DENIED;
	}
	new vehicleID = GetPlayerVehicleID(playerID);
	if(!vehicleID)
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	ShowDialog:SetSell(playerID);
	return COMMAND_OK;
}