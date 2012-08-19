ShowDialog:DrivingSchool_StartDriving(playerID)
{
	CreateDialog(playerID, "DrivingSchool_StartDriving", DIALOG_STYLE_MSGBOX, LanguageString(playerID, 599), LanguageString(playerID, 600), LanguageString(playerID, 166), LanguageString(playerID, 167));
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