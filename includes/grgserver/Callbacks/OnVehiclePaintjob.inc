public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	if (VehicleProperty:vehicleid[SAVEID])
	{
		MySQLQuery("UPDATE `vehicles` SET `paintjobId` = '%d' WHERE `id` = '%d'", paintjobid, VehicleProperty:vehicleid[SAVEID]);
	}
	return true;
}