/**
 * <summary>
 *	Destroyes all vehicles, creates the vehicles saved in the database, adds vehicle components and puts the NPCs in the vehicles if the ID of the vehicle is linked to a NPC.
 * </summary>
 *
 * <param name="modelID">
 *	The ID of the vehicle model which should be spawned.
 * </param>
 *
 * <param name="posX">
 *	The X-coordinate for the vehicle.
 * </param>
 *
 * <param name="posY">
 *	The Y-coordinate for the vehicle.
 * </param>
 *
 * <param name="posZ">
 *	The Z-coordinate for the vehicle.
 * </param>
 *
 * <param name="angle">
 *	The facing angle (Z rotation) of the vehicle.
 * </param>
 *
 * <param name="color1">
 *	The primary color ID.
 * </param>
 *
 * <param name="color2">
 *	The secondary color ID.
 * </param>
 *
 * <param name="respawnDelay">
 *	The delay in seconds until the vehicle gets respawned if there is no driver.
 * </param>
 *
 * <param name="isStatic">
 *	<item name="true">Use AddStaticVehicleEx for creating the vehicle (Only possible in OnGameModeInit and OnFilterScriptInit)</item>
 *	<item name="false">Use CreateVehicle for creating the vehicle (Can not spawn some trains)</item>
 * </param>
 *
 * <remarks>
 *	Vehicles with model ID 537 (Freight) and 538 (Streak) are only created if isStatic is set to true!
 * </remarks>
 */

CreateVehicleEx(modelID, Float:posX, Float:posY, Float:posZ, Float:angle, color1, color2, respawnDelay, isStatic)
{
	if (modelID >= 400 && modelID <= 611)
	{
		new vehicleID;
		new newColor1 = color1;
		new newColor2 = color2;
		if (color1 == -1 || color2 == -1)
		{
			GetVehicleColor(modelID, newColor1, newColor2);
		}
		if (isStatic)
		{
			vehicleID = AddStaticVehicleEx(modelID, posX, posY, posZ, angle, newColor1, newColor2, respawnDelay);
		}
		else
		{
			if (modelID == 537 || modelID == 538)// We can not spawn Freight and Streak using CreateVehicle
			{
				return 0;
			}
			vehicleID = CreateVehicle(modelID, posX, posY, posZ, angle, newColor1, newColor2, respawnDelay);
		}
		if (!vehicleID)
		{
			return 0;
		}
		SetVehicleParamsEx(vehicleID, false, false, false, false, false, false, false);
		Count(vehiclePropertyID, sizeof(vehicles[]))
		{
			vehicles[vehicleID][enum_vehicle:vehiclePropertyID] = 0;
		}
		VehicleProperty:vehicleID[ALLOWDESTROY] = true;
		VehicleProperty:vehicleID[COLOR1] = color1;
		VehicleProperty:vehicleID[COLOR2] = color2;
		VehicleProperty:vehicleID[CURRENTCOLOR1] = newColor1;
		VehicleProperty:vehicleID[CURRENTCOLOR2] = newColor2;
		VehicleProperty:vehicleID[CURRENTFUEL] = vehicleModels[modelID - 400][VEHICLEMODEL_MAXFUEL];
		return vehicleID;
	}
	return 0;
}