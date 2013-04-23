ShowDialog:UpgradeVehicle_Light(playerID)
{
	new options[1024];
	AddLine(options, LanguageString(playerID, StringID:362("")));
	AddLine(options, LanguageString(playerID, StringID:363("")));
	AddLine(options, LanguageString(playerID, StringID:364("")));
	AddLine(options, LanguageString(playerID, StringID:365("")));
	AddLine(options, LanguageString(playerID, StringID:366("")));
	AddLine(options, LanguageString(playerID, StringID:367("")));
	AddLine(options, LanguageString(playerID, StringID:368("")));
	AddLine(options, LanguageString(playerID, StringID:369("")));
	AddLine(options, LanguageString(playerID, StringID:370("")));
	AddLine(options, LanguageString(playerID, StringID:371("")));
	AddLine(options, LanguageString(playerID, StringID:372("")));
	AddLine(options, LanguageString(playerID, StringID:373("")));
	CreateDialog(playerID, "UpgradeVehicle_Light", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:376("")), options, "OK", LanguageString(playerID, StringID:171("")));
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
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:146(""));
		}
	}
	else
	{
		ShowDialog:UpgradeVehicle(playerID);
	}
}