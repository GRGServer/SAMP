CMD:setsell(playerID, params[], 495)
{
	if (PVar:playerID[JOBID] == JOB_VEHICLEDEALER)
	{
		new vehicleID = GetPlayerVehicleID(playerID);
		if(!vehicleID)
		{
			return COMMAND_NOT_IN_VEHICLE;
		}
		else
		{
			ShowDialog:SetSell(playerID);
			return COMMAND_OK;
		}
	}
	return COMMAND_PERMISSION_DENIED;
}