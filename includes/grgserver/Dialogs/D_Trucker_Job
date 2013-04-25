ShowDialog:Trucker_Job(playerID)
{
	CreateDialog(playerID, "VehicleDealer_Job", DIALOG_STYLE_MSGBOX, LanguageString(playerID, StringID:353("Vehicle dealer")), LanguageString(playerID, StringID:354("You are current no vehicle dealer.\n\nDo you want to accept the job?")), LanguageString(playerID, StringID:166("Yes")), LanguageString(playerID, StringID:167("No")));
}

DialogResponse:Trucker_Job(playerID, response, listItem, inputText[])
{
	if (response)
	{
		PVar:playerID[JOBID] = JOB_TRUCKER;
		SendClientMessageEx(playerID, COLOR_INFO, StringID:355("You are now Trucker"));
	}
}