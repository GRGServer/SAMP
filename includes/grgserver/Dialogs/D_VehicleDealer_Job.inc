ShowDialog:VehicleDealer_Job(playerID)
{
	CreateDialog(playerID, "VehicleDealer_Job", DIALOG_STYLE_MSGBOX, LanguageString(playerID, "353"), LanguageString(playerID, "354"), LanguageString(playerID, "166"), LanguageString(playerID, "167"));
}

DialogResponse:VehicleDealer_Job(playerID, response, listItem, inputText[])
{
	if (response)
	{
		PVar:playerID[JOBID] = JOB_VEHICLEDEALER;
		SendClientMessageEx(playerID, COLOR_INFO, "355");
	}
}