PCMD:mengine[MAPPER](playerID, params[], StringID:111("Start or stop the engine of your vehicle"))
{
	if (!IsPlayerInAnyVehicle(playerID))
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	if (GetPlayerState(playerID) != PLAYER_STATE_DRIVER)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:52("You are not the driver of this vehicle!"));
		return COMMAND_ERROR;
	}
	new vehicleID = GetPlayerVehicleID(playerID);
	if (GetVehicleEngineState(vehicleID))
	{
		SetVehicleEngineState(vehicleID, false);
		SendClientMessageEx(playerID, COLOR_INFO, StringID:53("The engine of your vehicle has been turned off."));
		return COMMAND_OK;
	}
	SetVehicleEngineState(vehicleID, true);
	SendClientMessageEx(playerID, COLOR_INFO, StringID:54("The engine of your vehicle has been turned on."));
	return COMMAND_OK;
}