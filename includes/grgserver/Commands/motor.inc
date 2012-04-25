CMD:motor(playerid, params[], 111)
{
	if (!IsPlayerInAnyVehicle(playerid))
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	{
		SendClientMessageEx(playerid, COLOR_ERROR, 52);
		return COMMAND_ERROR;
	}
	new vehicleID = GetPlayerVehicleID(playerid);
	if (!CheckVehiclePermission(playerid, vehicleID))
	{
		return COMMAND_ERROR;
	}
	if (GetVehicleEngineState(vehicleID))
	{
		SetVehicleEngineState(vehicleID, false);
		SendClientMessageEx(playerid, COLOR_INFO, 53);
		return COMMAND_OK;
	}
	new Float:health;
	GetVehicleHealth(vehicleID, health);
	if (health >= floatmul(VEHICLE_MINHEALTH, 10))
	{
		SetVehicleEngineState(vehicleID, true);
		if (vehicles[vehicleID][VEHICLE_RADIOSTATION])
		{
			PlayRadioStation(playerid, vehicles[vehicleID][VEHICLE_RADIOSTATION]);
		}
		SendClientMessageEx(playerid, COLOR_INFO, 54);
		return COMMAND_OK;
	}
	SendClientMessageEx(playerid, COLOR_ERROR, 55);
	return COMMAND_ERROR;
}