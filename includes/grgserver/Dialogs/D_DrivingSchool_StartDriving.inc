ShowDialog:DrivingSchool_StartDriving(playerID)
{
	CreateDialog(playerID, "DrivingSchool_StartDriving", DIALOG_STYLE_MSGBOX, LanguageString(playerID, StringID:599("")), LanguageString(playerID, StringID:600("")), LanguageString(playerID, StringID:166("")), LanguageString(playerID, StringID:167("")));
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