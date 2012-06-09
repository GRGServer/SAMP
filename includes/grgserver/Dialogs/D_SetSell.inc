ShowDialog:SetSell(playerID)
{
	CreateDialog(playerID, "SetSell", DIALOG_STYLE_INPUT, LanguageString(playerID, 495), LanguageString(playerID, 489), "OK", LanguageString(playerID, 165));
}

DialogResponse:SetSell(playerID, response, listItem, inputText[])
{
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:angle;
	new Float:health;
	new numberplateString[STRINGLENGTH_NUMBERPLATE];
	new vehicleID = GetPlayerVehicleID(playerID);
	new modelID = GetVehicleModel(vehicleID);
	if (!response)
	{
		return false;
	}
	new Float:price = floatstr(inputText);
	if (price <= 0)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 490);
		return false;
	}
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
		Format:sqlQuery("REPLACE INTO `vehicles` (`id`, `numberplate`, `posX`, `posY`, `posZ`, `angle`, `interior`, `health`, `modelId`, `color1`, `color2`, `price`, `currentFuel`)");
		MySQLQuery("%s VALUES('%d', '%s', '%f', '%f', '%f', '%f', '%d', '%f', '%d', '%d', '%d', '%f', '%f')", sqlQuery, VehicleProperty:vehicleID[SAVEID], numberplateString, posX, posY, posZ, angle, GetPlayerInterior(playerID), health, modelID, VehicleProperty:vehicleID[COLOR1], VehicleProperty:vehicleID[COLOR2], price, vehicleModels[modelID - 400][VEHICLEMODEL_MAXFUEL]);
		return COMMAND_OK;
	}
	SendClientMessageEx(playerID, COLOR_INFO, 491);
	RemovePlayerFromVehicle(playerID);
	return true;
}