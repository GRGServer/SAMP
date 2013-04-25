ShowDialog:Refuel(playerID)
{
	new string[80];
	GetStringArg(2, string);
	PVar:playerID[CURRENTGASPRICE] = gasPrice;
	Format:string(LanguageString(playerID, StringID:238("How much do you want to fill up (0 - %s)?\n\nCurrent price: $%s/Liter")), FormatNumber(PVar:playerID[REFUEL_MAXIMUM], 2, '.', ','), FormatMoney(gasPrice));
	CreateDialog(playerID, "Refuel", DIALOG_STYLE_INPUT, LanguageString(playerID, StringID:239("Refuel")), string, "OK", LanguageString(playerID, StringID:165("Cancel")));
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
			new Float:maximum = floatsub(vehicleModels[modelID - 400][VEHICLEMODEL_MAXFUEL], VehicleProperty:vehicleID[CURRENTFUEL]);
			if (amount > maximum)
			{
				amount = maximum;
			}
			TogglePlayerControllable(playerID, false);
			SetVehicleEngineState(vehicleID, false);
			GameTextForPlayer(playerID, LanguageString(playerID, StringID:265("Your vehicle gets filled up. Please wait...")), 3000, 4);
			Timer_RefuelVehicle(playerID, amount);
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:146("You are not in a vehicle!"));
		}
	}
}