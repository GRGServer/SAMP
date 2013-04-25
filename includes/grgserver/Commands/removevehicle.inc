PCMD:removevehicle[MAPPER](playerID, params[], StringID:455("Remove the current vehicle from the database"))
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!vehicleID)
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	if (!VehicleProperty:vehicleID[SAVEID])
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:456("This vehicle is not a saved vehicle!"));
		return COMMAND_ERROR;
	}
	MySQLQuery("DELETE FROM `vehiclecomponents` WHERE `vehicleId` = '%d'", VehicleProperty:vehicleID[SAVEID]);
	MySQLQuery("DELETE FROM `vehicles` WHERE `id` = '%d'", VehicleProperty:vehicleID[SAVEID]);
	MySQLQuery("DELETE FROM `originalvehicles` WHERE `id` = '%d'", VehicleProperty:vehicleID[SAVEID]);
	VehicleProperty:vehicleID[SAVEID] = 0;
	DestroyVehicle(vehicleID);
	SendClientMessageEx(playerID, COLOR_INFO, StringID:457("The vehicle has been removed"));
	return COMMAND_OK;
}