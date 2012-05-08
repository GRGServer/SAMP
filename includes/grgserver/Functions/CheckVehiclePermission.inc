CheckVehiclePermission(playerID, vehicleID)
{
	if (!vehicles[vehicleID][VEHICLE_SAVEID])
	{
		if (!permissions[playerID][PERMISSION_MAPPER])
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 129, GetPermissionName(PERMISSION_MAPPER));
			return false;
		}
		else
		{
			return true;
		}
	}
	if (vehicles[vehicleID][VEHICLE_JOBID])
	{
		if (PVar:playerID[JOBID] == vehicles[vehicleID][VEHICLE_JOBID])
		{
			return true;
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 327);
			return false;
		}
	}
	MySQLQuery("SELECT * FROM `vehicles` WHERE `ID` = '%d'", VehicleProperty:vehicleID[SAVEID]);
	mysql_store_result();
	new ownerUserID = strval(GetMySQLField("OwnerUserID"));
	new Float:price = floatstr(GetMySQLField("Price"));
	if (!ownerUserID && price)
	{
		ShowDialog(playerID, DIALOG_BUYVEHICLE, FormatMoney(price));
		return true;
	}
	if (ownerUserID)
	{
		if (ownerUserID == PVar:playerID[USERID])
		{
			return true;
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 130);
			return false;
		}
	}
	if (!price && !permissions[playerID][PERMISSION_MAPPER])
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 129, GetPermissionName(PERMISSION_MAPPER));
		return false;
	}
	return true;
}