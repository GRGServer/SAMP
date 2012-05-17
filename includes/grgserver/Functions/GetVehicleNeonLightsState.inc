GetVehicleNeonLightsState(vehicleID)
{
	Count(colorID, LIGHTOBJECT_MAXCOLORS)
	{
		if (vehicleLightObjects[vehicleID][NEONTYPE_LEFT][colorID] || vehicleLightObjects[vehicleID][NEONTYPE_RIGHT][colorID])
		{
			return true;
		}
	}
	return false;
}