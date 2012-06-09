public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	VehicleProperty:vehicleid[COLOR1] = color1;
	VehicleProperty:vehicleid[COLOR2] = color2;
	if (VehicleProperty:vehicleid[SAVEID])
	{
		MySQLQuery("UPDATE `vehicles` SET `color1` = '%d', `color2` = '%d' WHERE `id` = '%d'", color1, color2, VehicleProperty:vehicleid[SAVEID]);
	}
	return true;
}