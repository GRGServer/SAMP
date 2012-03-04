public OnVehicleDeath(vehicleid, killerid)
{
	if (vehicles[vehicleid][VEHICLE_SAVEID])
	{
		MySQLQuery("DELETE FROM `savedvehicles` WHERE `ID` = '%d'", vehicles[vehicleid][VEHICLE_SAVEID]);
		MySQLQuery("DELETE FROM `vehiclecomponents` WHERE `ID` = '%d'", vehicles[vehicleid][VEHICLE_SAVEID]);
		vehicles[vehicleid][VEHICLE_SAVEID] = 0;
	}
}