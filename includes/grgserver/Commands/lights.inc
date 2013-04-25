CMD:lights(playerID, params[], StringID:416("Turn on or off the lights of your vehicle"))
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!vehicleID)
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	if (GetPlayerState(playerID) != PLAYER_STATE_DRIVER)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:52("You are not the driver of this vehicle!"));
		return COMMAND_ERROR;
	}
	if (GetVehicleLightsState(vehicleID))
	{
		SetVehicleLightsState(vehicleID, false);
		SendClientMessageEx(playerID, COLOR_INFO, StringID:435("The lights of your vehicle were turned off"));
	}
	else
	{
		SetVehicleLightsState(vehicleID, true);
		SendClientMessageEx(playerID, COLOR_INFO, StringID:436("The lights of your vehicle were turned on"));
	}
	return COMMAND_OK;
}