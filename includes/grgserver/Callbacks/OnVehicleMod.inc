public OnVehicleMod(playerid, vehicleid, componentid)
{
	if (vehicles[vehicleid][VEHICLE_SAVEID])
	{
		MySQLQuery("REPLACE INTO `vehiclecomponents` (`VehicleID`, `Slot`, `Component`) VALUES('%d', '%d', '%d')", vehicles[vehicleid][VEHICLE_SAVEID], GetVehicleComponentType(componentid), componentid);
	}
	return true;
}