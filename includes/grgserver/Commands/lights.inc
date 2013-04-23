CMD:lights(playerID, params[], StringID:416(""))
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!vehicleID)
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	if (GetPlayerState(playerID) != PLAYER_STATE_DRIVER)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:52(""));
		return COMMAND_ERROR;
	}
	if (GetVehicleLightsState(vehicleID))
	{
		SetVehicleLightsState(vehicleID, false);
		SendClientMessageEx(playerID, COLOR_INFO, StringID:435(""));
	}
	else
	{
		SetVehicleLightsState(vehicleID, true);
		SendClientMessageEx(playerID, COLOR_INFO, StringID:436(""));
	}
	return COMMAND_OK;
}