CMD:sellvehicle(playerID, params[], StringID:488("Sell your vehicle"))
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!vehicleID)
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	if (!CheckVehiclePermission(playerID, vehicleID, false))
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:487("You are not the owner of this vehicle!"));
		return COMMAND_ERROR;
	}
	ShowDialog:SellVehicle(playerID);
	return COMMAND_OK;
}