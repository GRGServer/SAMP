CMD:lights(playerID, params[], 416)
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!vehicleID)
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	if (GetPlayerState(playerID) != PLAYER_STATE_DRIVER)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 52);
		return COMMAND_ERROR;
	}
	if (GetVehicleLightsState(vehicleID))
	{
		SetVehicleLightsState(vehicleID, false);
	}
	else
	{
		SetVehicleLightsState(vehicleID, true);
	}
	return COMMAND_OK;
}