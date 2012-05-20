PCMD:removevehicle[MAPPER](playerID, params[], 455)
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!vehicleID)
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	if (!VehicleProperty:vehicleID[SAVEID])
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 456);
		return COMMAND_ERROR;
	}
	MySQLQuery("DELETE FROM `vehicles` WHERE `ID` = '%d'", VehicleProperty:vehicleID[SAVEID]);
	VehicleProperty:vehicleID[SAVEID] = 0;
	DestroyVehicle(vehicleID);
	SendClientMessageEx(playerID, COLOR_INFO, 457);
	return COMMAND_OK;
}