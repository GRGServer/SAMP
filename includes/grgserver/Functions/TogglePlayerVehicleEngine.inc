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
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:52("You are not the driver of this vehicle!"));
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
		SendClientMessageEx(playerID, COLOR_INFO, StringID:53("The engine of your vehicle has been turned off."));
		return true;
	}

	new Float:health;
	GetVehicleHealth(vehicleID, health);
	if (health < VEHICLE_MINHEALTH)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:55("The engine of your vehicle could not be started (Engine damaged)!"));
		return false;
	}

	if (VehicleProperty:vehicleID[CURRENTFUEL] <= 0)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:159("The tank of your vehicle is empty!"));
		return false;
	}

	SetVehicleEngineState(vehicleID, true);
	if (VehicleProperty:vehicleID[RADIOSTATIONID])
	{
		PlayRadioStation(playerID, VehicleProperty:vehicleID[RADIOSTATIONID]);
	}
	SendClientMessageEx(playerID, COLOR_INFO, StringID:54("The engine of your vehicle has been turned on."));
	return true;
}