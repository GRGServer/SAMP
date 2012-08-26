public OnVehicleDeath(vehicleid, killerid)
{
	if (VehicleProperty:vehicleid[SAVEID] && VehicleProperty:vehicleid[ALLOWDESTROY])
	{
		MySQLQuery("DELETE FROM `vehicles` WHERE `id` = '%d'", VehicleProperty:vehicleid[SAVEID]);
		MySQLQuery("DELETE FROM `vehiclecomponents` WHERE `vehicleId` = '%d'", VehicleProperty:vehicleid[SAVEID]);
		VehicleProperty:vehicleid[SAVEID] = 0;
	}
}