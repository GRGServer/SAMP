CMD:navi(playerID, params[], 339)
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (vehicleID)
	{
		if (VehicleProperty:vehicleID[HASNAVI])
		{
			ShowDialog(playerID, DIALOG_NAVITARGET);
			return COMMAND_OK;
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 340);
			return COMMAND_ERROR;
		}
	}
	else
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
}