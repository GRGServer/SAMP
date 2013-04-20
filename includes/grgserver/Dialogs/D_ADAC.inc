ShowDialog:ADAC(playerID)
{
	FormatNew:options[50]("%s\n%s", LanguageString(playerID, "217"), LanguageString(playerID, "218"));
	CreateDialog(playerID, "ADAC", DIALOG_STYLE_LIST, LanguageString(playerID, "219"), options, LanguageString(playerID, "177"), LanguageString(playerID, "165"));
}

DialogResponse:ADAC(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0:
			{
				PVar:playerID[JOBID] = JOB_ADAC;
			}
			case 1:
			{
				PVar:playerID[JOBID] = 0;
			}
		}
	}
}