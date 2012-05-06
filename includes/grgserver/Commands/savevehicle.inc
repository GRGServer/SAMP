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
			new Float:health;
			new numberplateString[STRINGLENGTH_NUMBERPLATE];
			new vehicleID = GetPlayerVehicleID(playerID);
			new modelID = GetVehicleModel(vehicleID);
			if (modelID >= 400 && modelID <= 611)
			{
				GetVehiclePos(vehicleID, posX, posY, posZ);
				GetVehicleZAngle(vehicleID, angle);
				GetVehicleHealth(vehicleID, health);
				strcat(numberplateString, CreateUniqueNumberplateText());
				Format:sqlQuery("INSERT INTO `vehicles` (`Numberplate`, `PosX`, `PosY`, `PosZ`, `Angle`, `Interior`, `Health`, `ModelID`, `Color1`, `Color2`, `Price`, `CurrentFuel`)");
				MySQLQuery("%s VALUES('%s', '%f', '%f', '%f', '%f', '%d', '%f', '%d', '%d', '%d', '%f', '%f')", sqlQuery, numberplateString, posX, posY, posZ, angle, GetPlayerInterior(playerID), health, modelID, vehicles[vehicleID][VEHICLE_COLOR1], vehicles[vehicleID][VEHICLE_COLOR2], price, vehicleModels[modelID - 400][VEHICLEMODEL_MAXFUEL]);
				VehicleProperty:vehicleID[SAVEID] = mysql_insert_id();
				VehicleProperty:vehicleID[ALLOWSAVE] = true;
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
			return COMMAND_NOT_IN_VEHICLE;
		}
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 80);
	}
	return COMMAND_ERROR;
}