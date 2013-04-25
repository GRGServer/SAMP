ShowDialog:UpgradeVehicle_Light(playerID)
{
	new options[1024];
	AddLine(options, LanguageString(playerID, StringID:362("Dark blue")));
	AddLine(options, LanguageString(playerID, StringID:363("Gold")));
	AddLine(options, LanguageString(playerID, StringID:364("Green")));
	AddLine(options, LanguageString(playerID, StringID:365("Light blue")));
	AddLine(options, LanguageString(playerID, StringID:366("Light green")));
	AddLine(options, LanguageString(playerID, StringID:367("Orange")));
	AddLine(options, LanguageString(playerID, StringID:368("Pink")));
	AddLine(options, LanguageString(playerID, StringID:369("Purple")));
	AddLine(options, LanguageString(playerID, StringID:370("Red")));
	AddLine(options, LanguageString(playerID, StringID:371("Turquoise")));
	AddLine(options, LanguageString(playerID, StringID:372("White")));
	AddLine(options, LanguageString(playerID, StringID:373("Yellow")));
	CreateDialog(playerID, "UpgradeVehicle_Light", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:376("Add neon lights")), options, "OK", LanguageString(playerID, StringID:171("Back")));
}

DialogResponse:UpgradeVehicle_Light(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new vehicleID = GetPlayerVehicleID(playerID);
		if (vehicleID)
		{
			switch (PVar:playerID[UPGRADEVEHICLE_LIGHTTYPE])
			{
				case 1:
				{
					VehicleProperty:vehicleID[FRONTLIGHTID] = listItem + 1;
					SetVehicleLightsState(vehicleID, true);
				}
				case 2:
				{
					VehicleProperty:vehicleID[NEONLIGHTID] = listItem + 1;
					SetVehicleNeonLightsState(vehicleID, true);
				}
			}
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:146("You are not in a vehicle!"));
		}
	}
	else
	{
		ShowDialog:UpgradeVehicle(playerID);
	}
}