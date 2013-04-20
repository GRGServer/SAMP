CMD:navi(playerID, params[], 339)
{
	if (PVar:playerID[GPS_ENABLED])
	{
		PVar:playerID[GPS_ENABLED] = false;
		DisablePlayerRaceCheckpoint(playerID);
		SendClientMessageEx(playerID, COLOR_INFO, "460");
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
			SendClientMessageEx(playerID, COLOR_ERROR, "340");
			return COMMAND_ERROR;
		}
	}
	else
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
}