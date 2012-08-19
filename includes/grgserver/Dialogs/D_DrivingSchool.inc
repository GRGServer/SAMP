ShowDialog:DrivingSchool(playerID)
{
	new options[1024];
	if (!HasLicense(playerID, "Bike"))
	{
		AddLine(options, LanguageString(playerID, 533));
	}
	if (!HasLicense(playerID, "Car"))
	{
		AddLine(options, LanguageString(playerID, 530));
	}
	if (!HasLicense(playerID, "Trucker"))
	{
		AddLine(options, LanguageString(playerID, 532));
	}
	CreateDialog(playerID, "DrivingSchool", DIALOG_STYLE_LIST, LanguageString(playerID, 592), options, "OK", LanguageString(playerID, 165));
}

DialogResponse:DrivingSchool(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (IsStr(inputText, LanguageString(playerID, 533)))// Bike driving license
		{
			PVar:playerID[DRIVINGSCHOOL_TYPE] = DRIVINGSCHOOL_BIKE;
		}
		if (IsStr(inputText, LanguageString(playerID, 530)))// Car driving license
		{
			PVar:playerID[DRIVINGSCHOOL_TYPE] = DRIVINGSCHOOL_CAR;
		}
		if (IsStr(inputText, LanguageString(playerID, 532)))// Truck driving license
		{
			PVar:playerID[DRIVINGSCHOOL_TYPE] = DRIVINGSCHOOL_TRUCK;
		}
		TogglePlayerControllable(playerID, false);
		StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_DRVSCHOOL_ENTER, 0);
	}
}