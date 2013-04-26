ShowDialog:VehicleDealer_Options(playerID)
{
	new options[1024];
	if (PVar:playerID[ATWORK])
	{
		AddLine(options, LanguageString(playerID, StringID:356("End work")));
	}
	else
	{
		AddLine(options, LanguageString(playerID, StringID:357("Start work")));
	}
	AddLine(options, LanguageString(playerID, StringID:218("Cancel job")));
	CreateDialog(playerID, "VehicleDealer_Options", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:353("Vehicle dealer")), options, "OK", LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:VehicleDealer_Options(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (!strcmp(inputText, LanguageString(playerID, StringID:356("End work"))))// End work
		{
			PVar:playerID[ATWORK] = false;
			new time = gettime() - PVar:playerID[WORKSTARTTIME];
			SendClientMessageEx(playerID, COLOR_INFO, StringID:360("You have ended your working day. Worked hours: %d"), time / 60 / 60);
		}
		if (!strcmp(inputText, LanguageString(playerID, StringID:357("Start work"))))// Start work
		{
			PVar:playerID[ATWORK] = true;
			PVar:playerID[WORKSTARTTIME] = gettime();
			SetPlayerSkin(playerID, 187);
		}
		if (!strcmp(inputText, LanguageString(playerID, StringID:218("Cancel job"))))// Cancel job
		{
			PVar:playerID[JOBID] = JOB_UNEMPLOYED;
			SendClientMessageEx(playerID, COLOR_INFO, StringID:359("You have cancelled your job"));
			SetPlayerSkin(playerID, PVar:playerID[SKIN]);
		}
	}
}