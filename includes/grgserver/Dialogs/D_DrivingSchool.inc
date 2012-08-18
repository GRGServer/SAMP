ShowDialog:DrivingSchool(playerID)
{
	new options[1024];
	if (!HasLicense(playerID, "Car"))
	{
		AddLine(options, LanguageString(playerID, 530));
	}
	if (!HasLicense(playerID, "Trucker"))
	{
		AddLine(options, LanguageString(playerID, 532));
	}
	if (!HasLicense(playerID, "Bike"))
	{
		AddLine(options, LanguageString(playerID, 533));
	}
	CreateDialog(playerID, "DrivingSchool", DIALOG_STYLE_LIST, LanguageString(playerID, 592), options, "OK", LanguageString(playerID, 165));
}

DialogResponse:DrivingSchool(playerID, response, listItem, inputText[])
{
	if (response)
	{
		SendClientMessage(playerID, COLOR_SYSTEM, inputText);// TODO: Replace with working code  (e.g. save selected license type)
		TogglePlayerControllable(playerID, false);
		StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_DRVSCHOOL_ENTER_BLACK);
	}
}