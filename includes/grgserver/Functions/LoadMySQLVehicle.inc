/**
 * <summary>
 *	Load a vehicle from the current fetched MySQL row.
 * </summary>
 *
 * <param name="isStatic">
 *	<item name="true">Use AddStaticVehicleEx for creating the vehicle (Only possible in OnGameModeInit and OnFilterScriptInit)</item>
 *	<item name="false">Use CreateVehicle for creating the vehicle (Can not spawn some trains)</item>
 * </param>
 *
 * <param name="isSavedVehicle">
 *	<item name="true">The vehicle is loaded from the vehicles table</item>
 *	<item name="false">The vehicle is loaded from the originalvehicles table</item>
 * </param>
 *
 * <param name="playerID">
 *	The ID of the player which executes a command which loads the vehicle (Optional).
 * </param>
 *
 * <returns>
 *	<item name="true">The vehicle has been created successfully</item>
 *	<item name="false">An error occured while creating the vehicle</item>
 * </returns>
 */

LoadMySQLVehicle(isStatic, isSavedVehicle, playerID = INVALID_PLAYER_ID)
{
	new vehicleID = CreateVehicleEx(strval(GetMySQLField("modelId")), floatstr(GetMySQLField("posX")), floatstr(GetMySQLField("posY")), floatstr(GetMySQLField("posZ")), floatstr(GetMySQLField("angle")), strval(GetMySQLField("color1")), strval(GetMySQLField("color2")), isStatic);
	if (!vehicleID)
	{
		AdminPrint(playerID, COLOR_ERROR, "  Can not create vehicle '%d' (ModelID %d)!", strval(GetMySQLField("id")), strval(GetMySQLField("modelId")));
		return false;
	}
	VehicleProperty:vehicleID[FRONTLIGHTID] = strval(GetMySQLField("frontLightId"));
	VehicleProperty:vehicleID[HASNAVI] = strval(GetMySQLField("hasNavi"));
	VehicleProperty:vehicleID[JOBID] = strval(GetMySQLField("jobId"));
	VehicleProperty:vehicleID[MILEAGE] = floatstr(GetMySQLField("mileAge"));
	VehicleProperty:vehicleID[NEONLIGHTID] = strval(GetMySQLField("neonLightId"));
	VehicleProperty:vehicleID[PAINTJOBID] = strval(GetMySQLField("paintjobId"));
	VehicleProperty:vehicleID[PRICE] = floatstr(GetMySQLField("price"));
	VehicleProperty:vehicleID[SAVEID] = strval(GetMySQLField("id"));
	SetVehicleHealth(vehicleID, floatstr(GetMySQLField("health")));
	LinkVehicleToInterior(vehicleID, strval(GetMySQLField("interior")));
	LockVehicle(vehicleID, strval(GetMySQLField("locked")));
	ChangeVehiclePaintjob(vehicleID, VehicleProperty:vehicleID[PAINTJOBID]);
	if (isSavedVehicle)
	{
		VehicleProperty:vehicleID[CURRENTFUEL] = floatstr(GetMySQLField("currentFuel"));
		VehicleProperty:vehicleID[OWNERUSERID] = strval(GetMySQLField("ownerUserId"));
		VehicleProperty:vehicleID[RADIOSTATIONID] = strval(GetMySQLField("radioStationId"));
		VehicleProperty:vehicleID[SELLERUSERID] = strval(GetMySQLField("sellerUserId"));
		SetVehicleNumberPlate(vehicleID, GetMySQLField("numberplate"));
	}
	return true;
}