ShowDialog:AMBULANCE(playerID)
{
	FormatNew:options[50]("%s\n%s", LanguageString(playerID, 217), LanguageString(playerID, 218));
	CreateDialog(playerID, "AMBULANCE", DIALOG_STYLE_LIST, LanguageString(playerID, 221), options, LanguageString(playerID, 177), LanguageString(playerID, 165));
}

DialogResponse:AMBULANCE(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0:
			{
				PVar:playerID[JOBID] = JOB_AMBULANCE;
			}
			case 1:
			{
				PVar:playerID[JOBID] = 0;
			}
		}
	}
}