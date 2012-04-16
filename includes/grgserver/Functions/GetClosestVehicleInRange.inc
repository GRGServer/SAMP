GetClosestVehicleInRange(Float:posX, Float:posY, Float:posZ, Float:range, excludeVehicleID = 0)
{
	new Float:distance;
	new Float:lastDistance = range + 1;// Keep last distance high enought (Check if last distance was BIGGER) -> If lastDistance would be 0 -> There is never a closer vehicle (must be < 0 to find one which would never occur)
	new closestVehicleID = INVALID_VEHICLE_ID;
	Count(vehicleID, MAX_VEHICLES)
	{
		if (vehicleID != excludeVehicleID && GetVehicleModel(vehicleID) >= 400)
		{
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