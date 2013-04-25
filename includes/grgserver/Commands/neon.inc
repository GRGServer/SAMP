CMD:neon(playerID, params[], StringID:431("Turn on or off neon lights"))
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!vehicleID)
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	if (!VehicleProperty:vehicleID[NEONLIGHTID])
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:432("Your vehicle does not have neon lights!"));
		return COMMAND_ERROR;
	}
	if (GetVehicleNeonLightsState(vehicleID))
	{
		SetVehicleNeonLightsState(vehicleID, false);
		SendClientMessageEx(playerID, COLOR_INFO, StringID:433("The neon lights were turned off"));
	}
	else
	{
		SetVehicleNeonLightsState(vehicleID, true);
		SendClientMessageEx(playerID, COLOR_INFO, StringID:434("The neon lights were turned on"));
	}
	return COMMAND_OK;
}