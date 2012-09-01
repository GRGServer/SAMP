/**
 * <summary>
 *	Start or stop the engine of the current vehicle if the player has the permission and is the driver of the vehicle.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player which called the command.
 * </param>
 *
 * <param name="params">
 *	The parameters passed to this command (Unused).
 * </param>
 *
 * <returns>
 *	<item>COMMAND_ERROR</item>
 *	<item>COMMAND_NOT_IN_VEHICLE</item>
 *	<item>COMMAND_OK</item>
 * </returns>
 */

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
	if (VehicleProperty:vehicleID[ALLOWDRIVEPLAYERID] != playerID && !CheckVehiclePermission(playerID, vehicleID, true))
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
		if (VehicleProperty:vehicleID[RADIOSTATIONID])
		{
			PlayRadioStation(playerID, VehicleProperty:vehicleID[RADIOSTATIONID]);
		}
		SendClientMessageEx(playerID, COLOR_INFO, 54);
		return COMMAND_OK;
	}
	SendClientMessageEx(playerID, COLOR_ERROR, 55);
	return COMMAND_ERROR;
}