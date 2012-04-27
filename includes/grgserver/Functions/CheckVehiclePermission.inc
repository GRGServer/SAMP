CheckVehiclePermission(playerID, vehicleID)
{
	if (!vehicles[vehicleID][VEHICLE_SAVEID])
	{
		if (!permissions[playerID][PERMISSION_MAPPER])
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 129, GetPermissionName(PERMISSION_MAPPER));
			RemovePlayerFromVehicle(playerID);
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
			RemovePlayerFromVehicle(playerID);
			return false;
		}
	}
	new ownerUserID = strval(GetMySQLValue("savedvehicles", "OwnerUserID", "ID", val2str(vehicles[vehicleID][VEHICLE_SAVEID])));
	if (!ownerUserID)
	{
		ShowDialog(playerID, DIALOG_BUYVEHICLE, FormatMoney(floatstr(GetMySQLValue("savedvehicles", "Price", "ID", val2str(vehicles[vehicleID][VEHICLE_SAVEID])))));
		return true;
	}
	if (ownerUserID != PVar:playerID[USERID])
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 130);
		RemovePlayerFromVehicle(playerID);
		return false;
	}
	return true;
}