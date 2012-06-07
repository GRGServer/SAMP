CMD:vlock(playerID, params[], 483)
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
			SendClientMessageEx(playerID, COLOR_ERROR, 288);
			return COMMAND_ERROR;
		}
	}
	if (VehicleProperty:vehicleID[SAVEID])
	{
		MySQLQuery("SELECT `OwnerUserID` FROM `vehicles` WHERE `ID` = '%d'", VehicleProperty:vehicleID[SAVEID]);
		mysql_store_result();
		new ownerUserID = strval(GetMySQLField("OwnerUserID"));
		mysql_free_result();
		if (ownerUserID != PVar:playerID[USERID])
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 487);
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
		SendClientMessageEx(playerID, COLOR_INFO, 485);
	}
	else
	{
		LockVehicle(vehicleID, true);
		SendClientMessageEx(playerID, COLOR_INFO, 484);
	}
	return COMMAND_OK;
}