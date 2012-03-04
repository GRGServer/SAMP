public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	if (vehicles[vehicleid][VEHICLE_SAVEID])
	{
		MySQLQuery("UPDATE `savedvehicles` SET `Paintjob` = '%d' WHERE `ID` = '%d'", paintjobid, vehicles[vehicleid][VEHICLE_SAVEID]);
	}
	return true;
}