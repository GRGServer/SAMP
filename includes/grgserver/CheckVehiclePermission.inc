CheckVehiclePermission(playerID, vehicleID)
{
	if (!vehicles[vehicleID][VEHICLE_SAVEID])
	{
		if (!permissions[playerID][PERMISSION_MAPPER])
		{
			SendClientMessage(playerID, COLOR_ERROR, "Dieses Fahrzeug kann nur von der Gruppe 'Mapper' verwendet werden!");
			RemovePlayerFromVehicle(playerID);
			return false;
		}
		else
		{
			return true;
		}
	}
	new ownerUserID = strval(GetMySQLValue("savedvehicles", "OwnerUserID", "ID", val2str(vehicles[vehicleID][VEHICLE_SAVEID])));
	if (!ownerUserID)
	{
		ShowDialog(playerID, DIALOG_BUYVEHICLE, FormatMoney(floatstr(GetMySQLValue("savedvehicles", "Price", "ID", val2str(vehicles[vehicleID][VEHICLE_SAVEID])))));
		return true;
	}
	if (ownerUserID != GetPVar:playerID[USERID])
	{
		SendClientMessage(playerID, COLOR_ERROR, "Dieses Fahrzeug besitzt bereits ein anderer Spieler");
		RemovePlayerFromVehicle(playerID);
		return false;
	}
	return true;
}