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
	new Float:X,
		Float:Y,
		Float:Z,
		Float:Angle,
		Float:health = 10000.00,
		Float:currentfuel = 100.00;
	new modelID = GetVehicleModel(vehicleID);
	GetVehiclePos(vehicleID, X, Y, Z);
	GetVehicleZAngle(vehicleID, Angle);
	MySQLQuery("INSERT INTO `vehicles`(`numberplate`, `posX`, `posY`, `posZ`, `angle`, `price`, `health`, `modelId`, `color1`, `color2`, `currentFuel`) VALUES ('ND-%d%d%d%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%f')",random(5),random(5),random(5),random(5), X, Y, Z, Angle, price, health, modelID, 23+random(10), 23+random(10), currentfuel);
	SendClientMessageEx(playerID, COLOR_INFO, StringID:491("You have released your vehicle for sale"));
	RemovePlayerFromVehicle(playerID);
	return true;
}