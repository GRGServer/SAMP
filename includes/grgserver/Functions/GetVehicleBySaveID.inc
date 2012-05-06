GetVehicleBySaveID(saveID)
{
	if (saveID)
	{
		Count(vehicleID, MAX_VEHICLES)
		{
			if (VehicleProperty:vehicleID[SAVEID] == saveID)
			{
				return vehicleID;
			}
		}
	}
	return INVALID_VEHICLE_ID;
}