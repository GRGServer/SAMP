ShowDialog:UpgradeVehicle_Light(playerID)
{
	new options[1024];
	AddLine(options, LanguageString(playerID, "362"));
	AddLine(options, LanguageString(playerID, "363"));
	AddLine(options, LanguageString(playerID, "364"));
	AddLine(options, LanguageString(playerID, "365"));
	AddLine(options, LanguageString(playerID, "366"));
	AddLine(options, LanguageString(playerID, "367"));
	AddLine(options, LanguageString(playerID, "368"));
	AddLine(options, LanguageString(playerID, "369"));
	AddLine(options, LanguageString(playerID, "370"));
	AddLine(options, LanguageString(playerID, "371"));
	AddLine(options, LanguageString(playerID, "372"));
	AddLine(options, LanguageString(playerID, "373"));
	CreateDialog(playerID, "UpgradeVehicle_Light", DIALOG_STYLE_LIST, LanguageString(playerID, "376"), options, "OK", LanguageString(playerID, "171"));
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
			SendClientMessageEx(playerID, COLOR_ERROR, "146");
		}
	}
	else
	{
		ShowDialog:UpgradeVehicle(playerID);
	}
}