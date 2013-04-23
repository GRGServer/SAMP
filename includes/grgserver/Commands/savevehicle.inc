PCMD:savevehicle[MAPPER](playerID, params[], StringID:118(""))
{
	new Float:price;
	if (sscanf(params, "f", price))
	{
		CmdUsageMsg(playerID, "savevehicle", LanguageString(playerID, StringID:298("")));
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
			new vehicleID = GetPlayerVehicleID(playerID);
			new modelID = GetVehicleModel(vehicleID);
			if (modelID >= 400 && modelID <= 611)
			{
				GetVehiclePos(vehicleID, posX, posY, posZ);
				GetVehicleZAngle(vehicleID, angle);
				GetVehicleHealth(vehicleID, health);
				if (!VehicleProperty:vehicleID[SAVEID])
				{
					MySQLQuery("INSERT INTO `originalvehicles` (`modelId`) VALUES('%d')", modelID);
					VehicleProperty:vehicleID[SAVEID] = mysql_insert_id();
				}
				if (!VehicleProperty:vehicleID[SAVEID])
				{
					return COMMAND_ERROR;
				}
				VehicleProperty:vehicleID[PRICE] = price;
				SaveVehicle(vehicleID, GetPlayerInterior(playerID), true);
				SendClientMessageEx(playerID, COLOR_INFO, StringID:79(""), VehicleProperty:vehicleID[SAVEID]);
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
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:80(""));
	}
	return COMMAND_ERROR;
}