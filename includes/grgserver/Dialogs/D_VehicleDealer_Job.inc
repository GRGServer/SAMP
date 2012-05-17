ShowDialog:VehicleDealer_Job(playerID)
{
	ShowMsgBox(playerID, "VehicleDealer_Job", LanguageString(playerID, 353), LanguageString(playerID, 354), MSGBOXSTYLE_YESNO);
}

DialogResponse:VehicleDealer_Job(playerID, response, listItem, inputText[])
{
	if (response)
	{
		PVar:playerID[JOBID] = JOB_VEHICLEDEALER;
		SendClientMessageEx(playerID, COLOR_INFO, 355);
	}
}