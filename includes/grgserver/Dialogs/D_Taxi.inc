ShowDialog:Taxi(playerID)
{
	FormatNew:options[50]("%s\n%s", LanguageString(playerID, StringID:217("Accept job")), LanguageString(playerID, StringID:218("Cancel job")));
	CreateDialog(playerID, "Taxi", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:224("Taxi driver")), options, LanguageString(playerID, StringID:177("Next")), LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:Taxi(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0:
			{
				PVar:playerID[JOBID] = JOB_TAXI;
			}
			case 1:
			{
				PVar:playerID[JOBID] = 0;
			}
		}
	}
}