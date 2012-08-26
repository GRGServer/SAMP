public OnVehicleSpawn(vehicleid)
{
	if (VehicleProperty:vehicleid[ALLOWDESTROY])
	{
		RemoveVehicleLightObjects(vehicleid);
		DestroyVehicle(vehicleid);
	}
}