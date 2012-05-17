ShowDialog:UpgradeVehicle_Light(playerID)
{
	new options[1024];
	for (new stringID = 362; stringID <=373; stringID++)
	{
		AddLine(options, LanguageString(playerID, stringID));
	}
	CreateDialog(playerID, "UpgradeVehicle_Light", DIALOG_STYLE_LIST, LanguageString(playerID, 376), options, "OK", LanguageString(playerID, 171));
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
			SendClientMessageEx(playerID, COLOR_ERROR, 146);
		}
	}
	else
	{
		ShowDialog:UpgradeVehicle(playerID);
	}
}