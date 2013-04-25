ShowDialog:DrivingSchool_StartDriving(playerID)
{
	CreateDialog(playerID, "DrivingSchool_StartDriving", DIALOG_STYLE_MSGBOX, LanguageString(playerID, StringID:599("Driving school")), LanguageString(playerID, StringID:600("Are you ready to start to drive?")), LanguageString(playerID, StringID:166("Yes")), LanguageString(playerID, StringID:167("No")));
}

DialogResponse:DrivingSchool_StartDriving(playerID, response, listItem, inputText[])
{
	if (response)
	{
		ShowMessage(playerID, 26, 3000);
	}
	else
	{
		ShowMessage(playerID, 27, 3000);
	}
}