CMD:siren(playerID, params[], StringID:0(""))
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!vehicleID)
	{
		return COMMAND_NOT_IN_VEHICLE;
	}

	if (VehicleProperty:vehicleID[SIRENLIGHT])
	{
		DestroyObject(VehicleProperty:vehicleID[SIRENLIGHT]);
		VehicleProperty:vehicleID[SIRENLIGHT] = 0;
	}
	else
	{
		VehicleProperty:vehicleID[SIRENLIGHT] = CreateObject(18646, 0, 0, 0, 0, 0, 0);
		AttachObjectToVehicle(VehicleProperty:vehicleID[SIRENLIGHT], vehicleID, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0);
	}
	return COMMAND_OK;
}