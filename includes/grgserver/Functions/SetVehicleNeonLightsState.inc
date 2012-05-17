SetVehicleNeonLightsState(vehicleID, newState)
{
	if (newState)
	{
		AddNeonLight(vehicleID, NEONTYPE_LEFT, VehicleProperty:vehicleID[NEONLIGHTID] - 1);
		AddNeonLight(vehicleID, NEONTYPE_RIGHT, VehicleProperty:vehicleID[NEONLIGHTID] - 1);
	}
	else
	{
		Count(colorID, LIGHTOBJECT_MAXCOLORS)
		{
			if (vehicleLightObjects[vehicleID][NEONTYPE_LEFT][colorID])
			{
				DestroyDynamicObject(vehicleLightObjects[vehicleID][NEONTYPE_LEFT][colorID]);
				vehicleLightObjects[vehicleID][NEONTYPE_LEFT][colorID] = 0;
			}
			if (vehicleLightObjects[vehicleID][NEONTYPE_RIGHT][colorID])
			{
				DestroyDynamicObject(vehicleLightObjects[vehicleID][NEONTYPE_RIGHT][colorID]);
				vehicleLightObjects[vehicleID][NEONTYPE_RIGHT][colorID] = 0;
			}
		}
		UpdateObjectsForAllPlayers();
	}
}