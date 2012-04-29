CreateVehicleEx(modelID, Float:posX, Float:posY, Float:posZ, Float:angle, color1, color2, respawnDelay)
{
	if (modelID >= 400 && modelID <= 611)
	{
		new vehicleID = CreateVehicle(modelID, posX, posY, posZ, angle, color1, color2, respawnDelay);
		VehicleProperty:vehicleID[COLOR1] = color1;
		VehicleProperty:vehicleID[COLOR2] = color2;
		VehicleProperty:vehicleID[CURRENTFUEL] = vehicleModels[modelID - 400][VEHICLEMODEL_MAXFUEL];
		return vehicleID;
	}
	return 0;
}