public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	VehicleProperty:vehicleid[COLOR1] = color1;
	VehicleProperty:vehicleid[COLOR2] = color2;
	if (VehicleProperty:vehicleid[SAVEID])
	{
		MySQLQuery("UPDATE `vehicles` SET `Color1` = '%d', `Color2` = '%d' WHERE `ID` = '%d'", color1, color2, VehicleProperty:vehicleid[SAVEID]);
	}
	return true;
}