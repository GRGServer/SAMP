public OnVehicleDeath(vehicleid, killerid)
{
	if (VehicleProperty:vehicleid[SAVEID] && VehicleProperty:vehicleid[ALLOWSAVE])
	{
		if (strval(GetMySQLValue("vehicles", "OwnerUserID", "ID", val2str(VehicleProperty:vehicleid[SAVEID]))) > 0)
		{
			MySQLQuery("DELETE FROM `vehicles` WHERE `ID` = '%d'", VehicleProperty:vehicleid[SAVEID]);
			MySQLQuery("DELETE FROM `vehiclecomponents` WHERE `VehicleID` = '%d'", VehicleProperty:vehicleid[SAVEID]);
			VehicleProperty:vehicleid[SAVEID] = 0;
		}
		else
		{
			// TODO: Reload vehicle
		}
	}
	RemoveVehicleLightObjects(vehicleid);
}