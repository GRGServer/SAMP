public OnVehicleSpawn(vehicleid)
{
	if (VehicleProperty:vehicleid[ALLOWDESTROY])
	{
		DestroyVehicle(vehicleid);
	}
}