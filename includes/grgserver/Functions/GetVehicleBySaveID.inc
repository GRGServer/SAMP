GetVehicleBySaveID(saveID)
{
	if (saveID)
	{
		Count1(vehicleID, MAX_VEHICLES)
		{
			if (VehicleProperty:vehicleID[SAVEID] == saveID)
			{
				return vehicleID;
			}
		}
	}
	return 0;
}