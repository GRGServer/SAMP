public OnVehicleDeath(vehicleid, killerid)
{
	RemoveVehicleLightObjects(vehicleid);
	DestroyVehicle(vehicleid);
	if (VehicleProperty:vehicleid[SAVEID])
	{
		MySQLQuery("DELETE FROM `vehicles` WHERE `id` = '%d'", VehicleProperty:vehicleid[SAVEID]);
		MySQLQuery("DELETE FROM `vehiclecomponents` WHERE `vehicleId` = '%d'", VehicleProperty:vehicleid[SAVEID]);
		MySQLQuery("SELECT * FROM `originalvehicles` WHERE `id` = '%d'", VehicleProperty:vehicleid[SAVEID]);
		VehicleProperty:vehicleid[SAVEID] = 0;
		mysql_store_result();
		if (mysql_num_rows())
		{
			LoadMySQLVehicle(false, false);
		}
		mysql_free_result();
	}
}