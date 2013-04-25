CMD:navi(playerID, params[], StringID:339("Activate the navigation system"))
{
	if (PVar:playerID[GPS_ENABLED])
	{
		PVar:playerID[GPS_ENABLED] = false;
		DisablePlayerRaceCheckpoint(playerID);
		SendClientMessageEx(playerID, COLOR_INFO, StringID:460("The navigation system has been turned off"));
		return COMMAND_OK;
	}
	new vehicleID = GetPlayerVehicleID(playerID);
	if (vehicleID)
	{
		if (VehicleProperty:vehicleID[HASNAVI])
		{
			ShowDialog:NaviTarget(playerID);
			return COMMAND_OK;
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:340("Your vehicle does not have a navigation system!"));
			return COMMAND_ERROR;
		}
	}
	else
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
}