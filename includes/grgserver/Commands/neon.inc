CMD:neon(playerID, params[], StringID:431(""))
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!vehicleID)
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	if (!VehicleProperty:vehicleID[NEONLIGHTID])
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:432(""));
		return COMMAND_ERROR;
	}
	if (GetVehicleNeonLightsState(vehicleID))
	{
		SetVehicleNeonLightsState(vehicleID, false);
		SendClientMessageEx(playerID, COLOR_INFO, StringID:433(""));
	}
	else
	{
		SetVehicleNeonLightsState(vehicleID, true);
		SendClientMessageEx(playerID, COLOR_INFO, StringID:434(""));
	}
	return COMMAND_OK;
}