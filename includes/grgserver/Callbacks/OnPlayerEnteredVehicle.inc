/**
 * <summary>
 *	This callback gets called every time a player entered a vehicle.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player which entered the vehicle.
 * </param>
 *
 * <param name="vehicleID">
 *	The ID of the vehicle which was entered by the player.
 * </param>
 *
 * <param name="isPassenger">
 *	<item name="true">The player entered the vehicle as a passenger</item>
 *	<item name="false">The player entered the vehicle as the driver</item>
 * </param>
 *
 * <remarks>
 *	<title>Difference between OnPlayerEnterVehicle and OnPlayerEnteredVehicle:</title>
 *	<item name="OnPlayerEnterVehicle">The player is while entering the vehicle (Not already in the vehicle)</item>
 *	<item name="OnPlayerEnteredVehicle">The player is already in the vehicle</item>
 * </remarks>
 */

OnPlayerEnteredVehicle(playerID, vehicleID, isPassenger)
{
	if (IsPlayerNPC(playerID))
	{
		return true;
	}
	new modelID = GetVehicleModel(vehicleID);
	if (!isPassenger)
	{
		if (VehicleProperty:vehicleID[NPC_ONLY])
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:16("You are not allowed to drive this vehicle!"));
			return false;
		}
		if (modelID >= 400 && modelID <= 611)
		{
			if (IsStr(vehicleModels[modelID - 400][VEHICLEMODEL_TYPE], "Monster Truck"))
			{
				SendClientMessageEx(playerID, COLOR_WARNING, StringID:545("Remember: Monster trucks are prohibited on the street!"));
			}
			else
			{
				if (!HasLicense(playerID, vehicleModels[modelID - 400][VEHICLEMODEL_TYPE]) && !(PVar:playerID[CPMISSION_ID] && strfind(GetCheckpointMissionNameByID(PVar:playerID[CPMISSION_ID]), "DrivingSchool", true, 0) == 0))
				{
					SendClientMessageEx(playerID, COLOR_WARNING, StringID:514("You do not have a %l!"), GetLicenseLanguageStringID(vehicleModels[modelID - 400][VEHICLEMODEL_TYPE]));
					SendClientMessageEx(playerID, COLOR_WARNING, StringID:544("Do not get caught by the police!"));
				}
			}
		}
		if (PVar:playerID[CPMISSION_ID] && (!PVar:playerID[CPMISSION_VEHICLEID] || PVar:playerID[CPMISSION_VEHICLEID] == vehicleID))
		{
			DisablePlayerCheckpoint(playerID);
			NextMissionCheckpoint(playerID, true);
		}
	}
	if (!isPassenger && !GetVehicleEngineState(vehicleID))
	{
		SendClientMessageEx(playerID, COLOR_INFO, StringID:424("Use /engine to start the engine of your vehicle."));
	}
	SetVehicleParamsForPlayer(vehicleID, playerID, false, false);
	return true;
}