PCMD:savevehicle[MAPPER](playerID, params[], 118)
{
	new Float:price;
	if (sscanf(params, "f", price))
	{
		CmdUsageMsg(playerID, "savevehicle", LanguageString(playerID, 298));
		return COMMAND_USAGE;
	}
	if (price >= 0)
	{
		if (IsPlayerInAnyVehicle(playerID))
		{
			new Float:posX;
			new Float:posY;
			new Float:posZ;
			new Float:angle;
			new vehicleID = GetPlayerVehicleID(playerID);
			new modelID = GetVehicleModel(vehicleID);
			GetVehiclePos(vehicleID, posX, posY, posZ);
			GetVehicleZAngle(vehicleID, angle);
			MySQLQuery("INSERT INTO `savedvehicles` (`PosX`, `PosY`, `PosZ`, `Angle`, `Interior`, `ModelID`, `Color1`, `Color2`, `Price`, `CurrentFuel`) VALUES('%f', '%f', '%f', '%f', '%d', '%d', '%d', '%d', '%f', '%f')", posX, posY, posZ, angle, GetPlayerInterior(playerID), modelID, vehicles[vehicleID][VEHICLE_COLOR1], vehicles[vehicleID][VEHICLE_COLOR2], price, vehicleModels[modelID - 400][VEHICLEMODEL_MAXFUEL]);
			vehicles[vehicleID][VEHICLE_SAVEID] = mysql_insert_id();
			SendClientMessageEx(playerID, COLOR_INFO, 79, vehicles[vehicleID][VEHICLE_SAVEID]);
			return COMMAND_OK;
		}
		else
		{
			return COMMAND_NOT_IN_VEHICLE;
		}
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 80);
	}
	return COMMAND_ERROR;
}