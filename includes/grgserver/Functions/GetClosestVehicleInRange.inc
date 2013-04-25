GetClosestVehicleInRange(Float:posX, Float:posY, Float:posZ, Float:range, excludeVehicleID = 0, excludeOccupied = false, jobID = -1, type[STRINGLENGTH_VEHICLETYPE] = "")
{
	new Float:distance;
	new Float:lastDistance = range + 1;// Keep last distance high enought (Check if last distance was BIGGER) -> If lastDistance would be 0 -> There is never a closer vehicle (must be < 0 to find one which would never occur)
	new closestVehicleID;
	Count1(vehicleID, MAX_VEHICLES)
	{
		new modelID = GetVehicleModel(vehicleID);
		if (vehicleID != excludeVehicleID && (jobID == -1 || VehicleProperty:vehicleID[JOBID] == jobID) && modelID >= 400 && modelID <= 611 && (!StrNotNull(type) || IsStr(type, vehicleModels[modelID - 400][VEHICLEMODEL_TYPE])))
		{
			if (excludeOccupied)
			{
				PlayerLoop(playerID)
				{
					if (IsPlayerInVehicle(playerID, vehicleID))
					{
						continue;
					}
				}
			}
			distance = GetVehicleDistanceFromPoint(vehicleID, posX, posY, posZ);
			if (distance <= range && distance < lastDistance)
			{
				lastDistance = distance;
				closestVehicleID = vehicleID;
			}
		}
	}
	return closestVehicleID;
}