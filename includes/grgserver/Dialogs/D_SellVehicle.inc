ShowDialog:SellVehicle(playerID)
{
	CreateDialog(playerID, "SellVehicle", DIALOG_STYLE_INPUT, LanguageString(playerID, 486), LanguageString(playerID, 487), "OK", LanguageString(playerID, 165));
}

DialogResponse:SellVehicle(playerID, response, listItem, inputText[])
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (!response)
	{
		return false;
	}
	if (!StrNotNull(inputText))
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 488);
		return false;
	}
	SendClientMessageEx(playerID, COLOR_INFO, 489, inputText);
	MySQLQuery("UPDATE `vehicles` SET `Price` = '%f', `OwnerUserID` = '0', `OwnerSellerID` = '%d' WHERE `ID` = '%d'", floatstr(inputText), PVar:playerID[USERID], VehicleProperty:vehicleID[SAVEID]);
	RemovePlayerFromVehicle(playerID);
	return true;
}
