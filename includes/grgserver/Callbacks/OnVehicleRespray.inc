public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	vehicles[vehicleid][VEHICLE_COLOR1] = color1;
	vehicles[vehicleid][VEHICLE_COLOR2] = color2;
	if (vehicles[vehicleid][VEHICLE_SAVEID])
	{
		MySQLQuery("UPDATE `savedvehicles` SET `Color1` = '%d', `Color2` = '%d' WHERE `ID` = '%d'", color1, color2, vehicles[vehicleid][VEHICLE_SAVEID]);
	}
	return true;
}