ShowDialog:VehicleDealer_Job(playerID)
{
	CreateDialog(playerID, "VehicleDealer_Job", DIALOG_STYLE_MSGBOX, LanguageString(playerID, StringID:353("")), LanguageString(playerID, StringID:354("")), LanguageString(playerID, StringID:166("")), LanguageString(playerID, StringID:167("")));
}

DialogResponse:VehicleDealer_Job(playerID, response, listItem, inputText[])
{
	if (response)
	{
		PVar:playerID[JOBID] = JOB_VEHICLEDEALER;
		SendClientMessageEx(playerID, COLOR_INFO, StringID:355(""));
	}
}