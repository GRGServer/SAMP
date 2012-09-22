/**
 * <summary>
 *	Toggles the engine of the vehicle the player is currently driver of.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player
 * </param>
 *
 * <returns>
 *	<item name="true">The engine has been toggled</item>
 *	<item name="false">An error occured</item>
 * </returns>
 */

TogglePlayerVehicleEngine(playerID)
{
	if (GetPlayerState(playerID) != PLAYER_STATE_DRIVER)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 52);
		return false;
	}
	new vehicleID = GetPlayerVehicleID(playerID);
	if (VehicleProperty:vehicleID[ALLOWDRIVEPLAYERID] != playerID && !CheckVehiclePermission(playerID, vehicleID, true))
	{
		return true;
	}
	if (GetVehicleEngineState(vehicleID))
	{
		SetVehicleEngineState(vehicleID, false);
		SendClientMessageEx(playerID, COLOR_INFO, 53);
		return true;
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
		return true;
	}
	SendClientMessageEx(playerID, COLOR_ERROR, 55);
	return false;
}