public OnVehicleDeath(vehicleid, killerid)
{
	RemoveVehicleLightObjects(vehicleid);
	DestroyVehicle(vehicleid);
	if (VehicleProperty:vehicleid[SAVEID])
	{
		MySQLQuery("DELETE FROM `vehicles` WHERE `id` = '%d'", VehicleProperty:vehicleid[SAVEID]);
		MySQLQuery("DELETE FROM `vehiclecomponents` WHERE `vehicleId` = '%d'", VehicleProperty:vehicleid[SAVEID]);
	}
	Foreach(enumIndex, vehicles[])
	{
		vehicles[vehicleid - 1][enum_vehicle:enumIndex] = 0;
	}
}