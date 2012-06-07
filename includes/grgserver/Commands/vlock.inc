CMD:vlock(playerid, params[], 483)	
{
	new vehicleID = GetPlayerVehicleID(playerid);
	MySQLQuery("SELECT `ID` FROM `vehicles` WHERE `ID` = '%d' AND `Locked`", VehicleProperty:vehicleID[SAVEID]);
	mysql_store_result();
	new isLocked = mysql_num_rows();
	mysql_free_result();
	if (isLocked)
	{
		SendClientMessageEx(playerid, COLOR_INFO, 484);
		MySQLQuery("UPDATE `vehicles` SET `Locked`= '0' WHERE `ID` = '%d'", VehicleProperty:vehicleID[SAVEID]);
				
	}
	else
	{
		SendClientMessageEx(playerid, COLOR_INFO, 485);
		MySQLQuery("UPDATE `vehicles` SET `Locked` = '0' WHERE `ID` = '%d'", VehicleProperty:vehicleID[SAVEID]);
	}
	return COMMAND_OK;
}