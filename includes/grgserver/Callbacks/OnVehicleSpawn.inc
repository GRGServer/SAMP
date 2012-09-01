public OnVehicleSpawn(vehicleid)
{
	if (!VehicleProperty:vehicleid[SAVEID])
	{
		RemoveVehicleLightObjects(vehicleid);
		DestroyVehicle(vehicleid);
	}
}