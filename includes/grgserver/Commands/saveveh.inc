PCMD:saveveh[MAPPER](playerid, params[], 118)
{
	new Float:price;
	if (sscanf(params, "f", price))
	{
		CmdUsageMsg(playerid, "saveveh", "Preis");
		return COMMAND_USAGE;
	}
	if (price >= 0)
	{
		if (IsPlayerInAnyVehicle(playerid))
		{
			new Float:posX;
			new Float:posY;
			new Float:posZ;
			new Float:angle;
			new vehicleID = GetPlayerVehicleID(playerid);
			new modelID = GetVehicleModel(vehicleID);
			GetVehiclePos(vehicleID, posX, posY, posZ);
			GetVehicleZAngle(vehicleID, angle);
			MySQLQuery("INSERT INTO `savedvehicles` (`PosX`, `PosY`, `PosZ`, `Angle`, `Interior`, `ModelID`, `Color1`, `Color2`, `Price`, `CurrentFuel`) VALUES('%f', '%f', '%f', '%f', '%d', '%d', '%d', '%d', '%f', '%f')", posX, posY, posZ, angle, GetPlayerInterior(playerid), modelID, vehicles[vehicleID][VEHICLE_COLOR1], vehicles[vehicleID][VEHICLE_COLOR2], price, vehicleModels[modelID - 400][VEHICLEMODEL_MAXFUEL]);
			vehicles[vehicleID][VEHICLE_SAVEID] = mysql_insert_id();
			SendClientMessageEx(playerid, COLOR_INFO, 79, vehicles[vehicleID][VEHICLE_SAVEID]);
			return COMMAND_OK;
		}
		else
		{
			return COMMAND_NOT_IN_VEHICLE;
		}
	}
	else
	{
		SendClientMessageEx(playerid, COLOR_ERROR, 80);
	}
	return COMMAND_ERROR;
}