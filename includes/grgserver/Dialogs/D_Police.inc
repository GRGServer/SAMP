ShowDialog:Police(playerID)
{
	FormatNew:options[50]("%s\n%s", LanguageString(playerID, StringID:217("")), LanguageString(playerID, StringID:218("")));
	CreateDialog(playerID, "Police", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:224("")), options, LanguageString(playerID, StringID:177("")), LanguageString(playerID, StringID:165("")));
}

DialogResponse:Police(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0:
			{
				PVar:playerID[JOBID] = JOB_POLICE;
			}
			case 1:
			{
				PVar:playerID[JOBID] = 0;
			}
		}
	}
}