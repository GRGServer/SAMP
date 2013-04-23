ShowDialog:SellVehicle(playerID)
{
	CreateDialog(playerID, "SellVehicle", DIALOG_STYLE_INPUT, LanguageString(playerID, StringID:488("")), LanguageString(playerID, StringID:489("")), "OK", LanguageString(playerID, StringID:165("")));
}

DialogResponse:SellVehicle(playerID, response, listItem, inputText[])
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!response)
	{
		return true;
	}
	if (!vehicleID)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:146(""));
	}
	if (VehicleProperty:vehicleID[OWNERUSERID] != PVar:playerID[USERID])
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:487(""));
		return true;
	}
	new Float:price = floatstr(inputText);
	if (price <= 0)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:490(""));
		return true;
	}
	VehicleProperty:vehicleID[OWNERUSERID] = 0;
	VehicleProperty:vehicleID[PRICE] = price;
	VehicleProperty:vehicleID[SELLERUSERID] = PVar:playerID[USERID];
	SendClientMessageEx(playerID, COLOR_INFO, StringID:491(""), inputText);
	RemovePlayerFromVehicle(playerID);
	return true;
}