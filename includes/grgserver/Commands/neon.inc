CMD:neon(playerID, params[], 431)
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!vehicleID)
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	if (!VehicleProperty:vehicleID[NEONLIGHTID])
	{
		SendClientMessageEx(playerID, COLOR_ERROR, "432");
		return COMMAND_ERROR;
	}
	if (GetVehicleNeonLightsState(vehicleID))
	{
		SetVehicleNeonLightsState(vehicleID, false);
		SendClientMessageEx(playerID, COLOR_INFO, "433");
	}
	else
	{
		SetVehicleNeonLightsState(vehicleID, true);
		SendClientMessageEx(playerID, COLOR_INFO, "434");
	}
	return COMMAND_OK;
}