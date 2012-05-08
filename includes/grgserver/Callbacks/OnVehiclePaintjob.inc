public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	if (VehicleProperty:vehicleid[SAVEID])
	{
		MySQLQuery("UPDATE `vehicles` SET `PaintjobID` = '%d' WHERE `ID` = '%d'", paintjobid, VehicleProperty:vehicleid[SAVEID]);
	}
	return true;
}