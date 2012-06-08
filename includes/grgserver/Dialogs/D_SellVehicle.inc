ShowDialog:SellVehicle(playerID)
{
	CreateDialog(playerID, "SellVehicle", DIALOG_STYLE_INPUT, LanguageString(playerID, 488), LanguageString(playerID, 489), "OK", LanguageString(playerID, 165));
}

DialogResponse:SellVehicle(playerID, response, listItem, inputText[])
{
	new vehicleID = GetPlayerVehicleID(playerID);
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
	SendClientMessageEx(playerID, COLOR_INFO, 491, inputText);
	MySQLQuery("UPDATE `vehicles` SET `Price` = '%f', `OwnerUserID` = '0', `OwnerSellerID` = '%d' WHERE `ID` = '%d'", price, PVar:playerID[USERID], VehicleProperty:vehicleID[SAVEID]);
	RemovePlayerFromVehicle(playerID);
	return true;
}