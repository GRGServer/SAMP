ShowDialog:Refuel(playerID)
{
	new string[80];
	GetStringArg(2, string);
	PVar:playerID[CURRENTGASPRICE] = gasPrice;
	Format:string(LanguageString(playerID, 238), FormatNumber(PVar:playerID[REFUEL_MAXIMUM], 2, '.', ','), FormatMoney(gasPrice));
	CreateDialog(playerID, "Refuel", DIALOG_STYLE_INPUT, LanguageString(playerID, 239), string, "OK", LanguageString(playerID, 165));
}

DialogResponse:Refuel(playerID, response, listItem, inputText[])
{
	if (response && strlen(inputText))
	{
		new Float:amount = floatstr(inputText);
		new vehicleID = GetPlayerVehicleID(playerID);
		new modelID = GetVehicleModel(vehicleID);
		if (modelID >= 400 && modelID <= 611)
		{
			new Float:maximum = floatsub(vehicleModels[modelID - 400][VEHICLEMODEL_MAXFUEL], vehicles[vehicleID][VEHICLE_CURRENTFUEL]);
			if (amount > maximum)
			{
				amount = maximum;
			}
			TogglePlayerControllable(playerID, false);
			SetVehicleEngineState(vehicleID, false);
			GameTextForPlayer(playerID, LanguageString(playerID, 265), 3000, 4);
			Timer_RefuelVehicle(playerID, amount);
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 146);
		}
	}
}