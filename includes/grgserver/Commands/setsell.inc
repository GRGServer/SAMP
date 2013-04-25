CMD:setsell(playerID, params[], StringID:495("Allow your vehicle to get bought by a vehicle dealer"))
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