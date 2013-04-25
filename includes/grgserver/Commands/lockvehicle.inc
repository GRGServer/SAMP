CMD:lockvehicle(playerID, params[], StringID:483("Lock or unlock a vehicle"))
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!vehicleID)
	{
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		GetPlayerPos(playerID, posX, posY, posZ);
		vehicleID = GetClosestVehicleInRange(posX, posY, posZ, 5);
		if (!vehicleID)
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:288("There is no vehicle in range!"));
			return COMMAND_ERROR;
		}
	}
	if (VehicleProperty:vehicleID[SAVEID])
	{
		if (VehicleProperty:vehicleID[OWNERUSERID] != PVar:playerID[USERID])
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:487("You are not the owner of this vehicle!"));
			return COMMAND_ERROR;
		}
	}
	else
	{
		if (!permissions[playerID][PERMISSION_MAPPER])
		{
			return COMMAND_PERMISSION_DENIED;
		}
	}
	if (IsVehicleLocked(vehicleID))
	{
		LockVehicle(vehicleID, false);
		SendClientMessageEx(playerID, COLOR_INFO, StringID:485("The vehicle has been unlocked!"));
	}
	else
	{
		LockVehicle(vehicleID, true);
		SendClientMessageEx(playerID, COLOR_INFO, StringID:484("The vehicle has been locked!"));
	}
	return COMMAND_OK;
}