CreateVehicleEx(modelID, Float:posX, Float:posY, Float:posZ, Float:angle, color1, color2, respawnDelay, isStatic)
{
	if (modelID >= 400 && modelID <= 611)
	{
		new vehicleID;
		if (isStatic)
		{
			vehicleID = AddStaticVehicleEx(modelID, posX, posY, posZ, angle, color1, color2, respawnDelay);
		}
		else
		{
			if (modelID == 537 || modelID == 538)// We can not spawn Freight and Streak using CreateVehicle
			{
				return false;
			}
			vehicleID = CreateVehicle(modelID, posX, posY, posZ, angle, color1, color2, respawnDelay);
		}
		if (!vehicleID)
		{
			return 0;
		}
		SetVehicleParamsEx(vehicleID, false, false, false, false, false, false, false);
		Count(vehiclePropertyID, sizeof(vehicles[]))
		{
			vehicles[vehicleID][enum_vehicle:vehiclePropertyID] = 0;
		}
		VehicleProperty:vehicleID[ALLOWDESTROY] = true;
		VehicleProperty:vehicleID[COLOR1] = color1;
		VehicleProperty:vehicleID[COLOR2] = color2;
		VehicleProperty:vehicleID[CURRENTFUEL] = vehicleModels[modelID - 400][VEHICLEMODEL_MAXFUEL];
		return vehicleID;
	}
	return 0;
}