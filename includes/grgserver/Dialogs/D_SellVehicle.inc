ShowDialog:SellVehicle(playerID)
{
	CreateDialog(playerID, "SellVehicle", DIALOG_STYLE_INPUT, LanguageString(playerID, StringID:488("Sell your vehicle")), LanguageString(playerID, StringID:489("Enter the sale price.")), "OK", LanguageString(playerID, StringID:165("Cancel")));
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
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:146("You are not in a vehicle!"));
	}
	if (VehicleProperty:vehicleID[OWNERUSERID] != PVar:playerID[USERID])
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:487("You are not the owner of this vehicle!"));
		return true;
	}
	new Float:price = floatstr(inputText);
	if (price <= 0)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:490("The price must be positive!"));
		return true;
	}
	VehicleProperty:vehicleID[OWNERUSERID] = 0;
	VehicleProperty:vehicleID[PRICE] = price;
	VehicleProperty:vehicleID[SELLERUSERID] = PVar:playerID[USERID];
	SendClientMessageEx(playerID, COLOR_INFO, StringID:491("You have released your vehicle for sale"), inputText);
	RemovePlayerFromVehicle(playerID);
	return true;
}