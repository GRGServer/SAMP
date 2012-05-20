public OnVehicleDeath(vehicleid, killerid)
{
	if (VehicleProperty:vehicleid[SAVEID] && VehicleProperty:vehicleid[ALLOWSAVE])
	{
		MySQLQuery("DELETE FROM `vehicles` WHERE `ID` = '%d'", VehicleProperty:vehicleid[SAVEID]);
		MySQLQuery("DELETE FROM `vehiclecomponents` WHERE `VehicleID` = '%d'", VehicleProperty:vehicleid[SAVEID]);
		VehicleProperty:vehicleid[SAVEID] = 0;
	}
	RemoveVehicleLightObjects(vehicleid);
}