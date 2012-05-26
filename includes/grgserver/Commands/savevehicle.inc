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
				if (!VehicleProperty:vehicleID[SAVEID])
				{
					MySQLQuery("INSERT INTO `vehicles` VALUES()");
					VehicleProperty:vehicleID[SAVEID] = mysql_insert_id();
					if (!VehicleProperty:vehicleID[SAVEID])
					{
						return COMMAND_ERROR;
					}
				}
				Format:sqlQuery("REPLACE INTO `vehicles` (`ID`, `Numberplate`, `PosX`, `PosY`, `PosZ`, `Angle`, `Interior`, `Health`, `ModelID`, `Color1`, `Color2`, `Price`, `CurrentFuel`)");
				MySQLQuery("%s VALUES('%d', '%s', '%f', '%f', '%f', '%f', '%d', '%f', '%d', '%d', '%d', '%f', '%f')", sqlQuery, VehicleProperty:vehicleID[SAVEID], numberplateString, posX, posY, posZ, angle, GetPlayerInterior(playerID), health, modelID, VehicleProperty:vehicleID[COLOR1], VehicleProperty:vehicleID[COLOR2], price, vehicleModels[modelID - 400][VEHICLEMODEL_MAXFUEL]);
				SendClientMessageEx(playerID, COLOR_INFO, 79, VehicleProperty:vehicleID[SAVEID]);
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