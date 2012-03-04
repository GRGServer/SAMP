CreateVehicleEx(modelID, Float:posX, Float:posY, Float:posZ, Float:angle, color1, color2, respawnDelay, Float:fuel = -1.0, saveID = 0, jobID = 0)
{
	if (fuel < 0)
	{
		fuel = vehicleModels[modelID - 400][VEHICLEMODEL_MAXFUEL];
	}
	new vehicleID = CreateVehicle(modelID, posX, posY, posZ, angle, color1, color2, respawnDelay);
	vehicles[vehicleID][VEHICLE_COLOR1] = color1;
	vehicles[vehicleID][VEHICLE_COLOR2] = color2;
	vehicles[vehicleID][VEHICLE_CURRENTFUEL] = fuel;
	vehicles[vehicleID][VEHICLE_JOBID] = jobID;
	vehicles[vehicleID][VEHICLE_SAVEID] = saveID;
	return vehicleID;
}