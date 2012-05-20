CMD:engine(playerID, params[], 111)
{
	if (!IsPlayerInAnyVehicle(playerID))
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	if (GetPlayerState(playerID) != PLAYER_STATE_DRIVER)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 52);
		return COMMAND_ERROR;
	}
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!CheckVehiclePermission(playerID, vehicleID))
	{
		return COMMAND_OK;
	}
	if (GetVehicleEngineState(vehicleID))
	{
		SetVehicleEngineState(vehicleID, false);
		SendClientMessageEx(playerID, COLOR_INFO, 53);
		return COMMAND_OK;
	}
	new Float:health;
	GetVehicleHealth(vehicleID, health);
	if (health >= floatmul(VEHICLE_MINHEALTH, 10))
	{
		SetVehicleEngineState(vehicleID, true);
		if (VehicleProperty:vehicleID[RADIOSTATION])
		{
			PlayRadioStation(playerID, VehicleProperty:vehicleID[RADIOSTATION]);
		}
		SendClientMessageEx(playerID, COLOR_INFO, 54);
		return COMMAND_OK;
	}
	SendClientMessageEx(playerID, COLOR_ERROR, 55);
	return COMMAND_ERROR;
}