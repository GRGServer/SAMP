ShowDialog:VEHICLEDEALER_JOB(playerID)
{
	ShowMsgBox(playerID, "VEHICLEDEALER_JOB", LanguageString(playerID, 353), LanguageString(playerID, 354), MSGBOXSTYLE_YESNO);
}

DialogResponse:VEHICLEDEALER_JOB(playerID, response, listItem, inputText[])
{
	if (response)
	{
		PVar:playerID[JOBID] = JOB_VEHICLEDEALER;
		SendClientMessageEx(playerID, COLOR_INFO, 355);
	}
}