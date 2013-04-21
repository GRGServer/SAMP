ShowDialog:DrivingSchool(playerID)
{
	new options[1024];
	if (!HasLicense(playerID, "Bike"))
	{
		AddLine(options, LanguageString(playerID, "LICENSE_BIKE"));
	}
	if (!HasLicense(playerID, "Car"))
	{
		AddLine(options, LanguageString(playerID, "LICENSE_CAR"));
	}
	if (!HasLicense(playerID, "Trucker"))
	{
		AddLine(options, LanguageString(playerID, "LICENSE_TRUCK"));
	}
	CreateDialog(playerID, "DrivingSchool", DIALOG_STYLE_LIST, LanguageString(playerID, "592"), options, "OK", LanguageString(playerID, "165"));
}

DialogResponse:DrivingSchool(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (IsStr(inputText, LanguageString(playerID, "LICENSE_BIKE")))// Bike driving license
		{
			PVar:playerID[DRIVINGSCHOOL_TYPE] = DRIVINGSCHOOL_BIKE;
		}
		if (IsStr(inputText, LanguageString(playerID, "LICENSE_CAR")))// Car driving license
		{
			PVar:playerID[DRIVINGSCHOOL_TYPE] = DRIVINGSCHOOL_CAR;
		}
		if (IsStr(inputText, LanguageString(playerID, "LICENSE_TRUCK")))// Truck driving license
		{
			PVar:playerID[DRIVINGSCHOOL_TYPE] = DRIVINGSCHOOL_TRUCK;
		}
		TogglePlayerControllable(playerID, false);
		StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_DRVSCHOOL_ENTER, 0);
	}
}