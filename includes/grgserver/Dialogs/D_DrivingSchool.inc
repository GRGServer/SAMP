ShowDialog:DrivingSchool(playerID)
{
	new options[1024];
	if (!HasLicense(playerID, "Bike"))
	{
		AddLine(options, LanguageString(playerID, StringID:533("Bike driving license")));
	}
	if (!HasLicense(playerID, "Car"))
	{
		AddLine(options, LanguageString(playerID, StringID:530("Car driving license")));
	}
	if (!HasLicense(playerID, "Trucker"))
	{
		AddLine(options, LanguageString(playerID, StringID:532("Truck driving license")));
	}
	CreateDialog(playerID, "DrivingSchool", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:592("Select driving license")), options, "OK", LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:DrivingSchool(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (IsStr(inputText, LanguageString(playerID, StringID:533("Bike driving license"))))// Bike driving license
		{
			PVar:playerID[DRIVINGSCHOOL_TYPE] = DRIVINGSCHOOL_BIKE;
		}
		if (IsStr(inputText, LanguageString(playerID, StringID:530("Car driving license"))))// Car driving license
		{
			PVar:playerID[DRIVINGSCHOOL_TYPE] = DRIVINGSCHOOL_CAR;
		}
		if (IsStr(inputText, LanguageString(playerID, StringID:532("Truck driving license"))))// Truck driving license
		{
			PVar:playerID[DRIVINGSCHOOL_TYPE] = DRIVINGSCHOOL_TRUCK;
		}
		TogglePlayerControllable(playerID, false);
		StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_DRVSCHOOL_ENTER, 0);
	}
}