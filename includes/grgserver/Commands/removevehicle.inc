PCMD:removevehicle[MAPPER](playerID, params[], StringID:455(""))
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!vehicleID)
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	if (!VehicleProperty:vehicleID[SAVEID])
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:456(""));
		return COMMAND_ERROR;
	}
	MySQLQuery("DELETE FROM `vehiclecomponents` WHERE `vehicleId` = '%d'", VehicleProperty:vehicleID[SAVEID]);
	MySQLQuery("DELETE FROM `vehicles` WHERE `id` = '%d'", VehicleProperty:vehicleID[SAVEID]);
	MySQLQuery("DELETE FROM `originalvehicles` WHERE `id` = '%d'", VehicleProperty:vehicleID[SAVEID]);
	VehicleProperty:vehicleID[SAVEID] = 0;
	DestroyVehicle(vehicleID);
	SendClientMessageEx(playerID, COLOR_INFO, StringID:457(""));
	return COMMAND_OK;
}