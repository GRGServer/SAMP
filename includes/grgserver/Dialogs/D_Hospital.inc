ShowDialog:Hospital(playerID)
{
	FormatNew:options[50]("%s\n%s", LanguageString(playerID, StringID:217("Accept job")), LanguageString(playerID, StringID:218("Cancel job")));
	CreateDialog(playerID, "Hospital", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:221("Ambulance")), options, LanguageString(playerID, StringID:177("Next")), LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:Hospital(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0:
			{
				PVar:playerID[JOBID] = JOB_PARAMEDIC;
			}
			case 1:
			{
				PVar:playerID[JOBID] = 0;
			}
		}
	}
}