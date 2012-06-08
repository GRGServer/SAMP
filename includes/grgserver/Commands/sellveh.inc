CMD:sellveh(playerID, params[], 486)
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!vehicleID)
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	if (CheckVehiclePermission(playerID, vehicleID))
	{
		ShowDialog:SellVehicle(playerID);
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 490);
	}
	return COMMAND_OK;
}