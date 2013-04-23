ShowDialog:VehicleDealer_Options(playerID)
{
	new options[1024];
	if (PVar:playerID[ATWORK])
	{
		AddLine(options, LanguageString(playerID, StringID:356("")));
	}
	else
	{
		AddLine(options, LanguageString(playerID, StringID:357("")));
	}
	AddLine(options, LanguageString(playerID, StringID:358("")));
	CreateDialog(playerID, "VehicleDealer_Options", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:353("")), options, "OK", LanguageString(playerID, StringID:165("")));
}

DialogResponse:VehicleDealer_Options(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (!strcmp(inputText, LanguageString(playerID, StringID:356(""))))// End work
		{
			PVar:playerID[ATWORK] = false;
			new time = gettime() - PVar:playerID[WORKSTARTTIME];
			SendClientMessageEx(playerID, COLOR_INFO, StringID:360(""), time / 60 / 60);
		}
		if (!strcmp(inputText, LanguageString(playerID, StringID:357(""))))// Start work
		{
			PVar:playerID[ATWORK] = true;
			PVar:playerID[WORKSTARTTIME] = gettime();
			SetPlayerSkin(playerID, 187);
		}
		if (!strcmp(inputText, LanguageString(playerID, StringID:358(""))))// Cancel job
		{
			PVar:playerID[JOBID] = JOB_UNEMPLOYED;
			SendClientMessageEx(playerID, COLOR_INFO, StringID:359(""));
			SetPlayerSkin(playerID, PVar:playerID[SKIN]);
		}
	}
}