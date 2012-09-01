ShowDialog:SetSell(playerID)
{
	CreateDialog(playerID, "SetSell", DIALOG_STYLE_INPUT, LanguageString(playerID, 495), LanguageString(playerID, 489), "OK", LanguageString(playerID, 165));
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
		SendClientMessageEx(playerID, COLOR_ERROR, 146);
		return false;
	}
	new Float:price = floatstr(inputText);
	if (price <= 0)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 490);
		return false;
	}
	SendClientMessage(playerID, COLOR_SYSTEM, "Coming soon");
	// TODO: Rewrite code
	//SendClientMessageEx(playerID, COLOR_INFO, 491);
	//RemovePlayerFromVehicle(playerID);
	return true;
}