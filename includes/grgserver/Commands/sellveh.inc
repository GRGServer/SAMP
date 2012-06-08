CMD:sellveh(playerID, params[], 488)
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!vehicleID)
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	if (!CheckVehiclePermission(playerID, vehicleID))
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 487);
		return COMMAND_ERROR;
	}
	ShowDialog:SellVehicle(playerID);
	return COMMAND_OK;
}