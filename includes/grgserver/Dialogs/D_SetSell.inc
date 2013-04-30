ShowDialog:SetSell(playerID)
{
	CreateDialog(playerID, "SetSell", DIALOG_STYLE_INPUT, LanguageString(playerID, StringID:495("Allow your vehicle to get bought by a vehicle dealer")), LanguageString(playerID, StringID:489("Enter the sale price.")), "OK", LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:SetSell(playerID, response, listItem, inputText[])
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!response)
	{
		return false;
	}
	if (!vehicleID)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:146("You are not in a vehicle!"));
		return false;
	}
	new Float:price = floatstr(inputText);
	if (price <= 0)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:490("The price must be positive!"));
		return false;
	}
	new color1, color2;
	new Float:X,
		Float:Y,
		Float:Z,
		Float:health = 100.00;
	GetPlayerPos(playerID, X, Y, Z);
	MySQLQuery("INSERT INTO `vehicles`(`numberplate`, `posX`, `posY`, `posZ`, `health`, `modelId`, `color1`, `color2`) VALUES ('ND-%d%d%d%d', '%f', '%f', '%f', '%f', '%d', '%d', '%d')",random(5),random(5),random(5),random(5), X, Y, Z, health, vehicleID, color1, color2);
	VehicleProperty:vehicleID[OWNERUSERID] = 0;
	VehicleProperty:vehicleID[PRICE] = price;
	VehicleProperty:vehicleID[SELLERUSERID] = PVar:playerID[USERID];
	SendClientMessageEx(playerID, COLOR_INFO, StringID:491("You have released your vehicle for sale"));
	RemovePlayerFromVehicle(playerID);
	return true;
}