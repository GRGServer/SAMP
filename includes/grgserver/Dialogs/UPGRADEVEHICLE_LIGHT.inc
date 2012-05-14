ShowDialog:UPGRADEVEHICLE_LIGHT(playerID)
{
	new options[1024];
	for (new stringID = 362; stringID <=373; stringID++)
	{
		AddLine(options, LanguageString(playerID, stringID));
	}
	CreateDialog(playerID, "UPGRADEVEHICLE_LIGHT", DIALOG_STYLE_LIST, LanguageString(playerID, 376), options, "OK", LanguageString(playerID, 171));
}

DialogResponse:UPGRADEVEHICLE_LIGHT(playerID, response, listItem, inputText[])
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
					AddNeonLight(vehicleID, NEONTYPE_FRONT_LEFT, listItem);
					AddNeonLight(vehicleID, NEONTYPE_FRONT_RIGHT, listItem);
					VehicleProperty:vehicleID[FRONTLIGHTID] = listItem + 1;
				}
				case 2:
				{
					AddNeonLight(vehicleID, NEONTYPE_LEFT, listItem);
					AddNeonLight(vehicleID, NEONTYPE_RIGHT, listItem);
					VehicleProperty:vehicleID[NEONLIGHTID] = listItem + 1;
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
		ShowDialog:UPGRADEVEHICLE(playerID);
	}
}