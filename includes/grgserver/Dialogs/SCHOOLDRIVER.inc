ShowDialog:SCHOOLDRIVER(playerID)
{
	FormatNew:options[50]("%s\n%s", LanguageString(playerID, 217), LanguageString(playerID, 218));
	CreateDialog(playerID, "SCHOOLDRIVER", DIALOG_STYLE_LIST, LanguageString(playerID, 223), options, LanguageString(playerID, 177), LanguageString(playerID, 165));
}

DialogResponse:SCHOOLDRIVER(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0:
			{
				PVar:playerID[JOBID] = JOB_SCHOOLDRIVER;
			}
			case 1:
			{
				PVar:playerID[JOBID] = 0;
			}
		}
	}
}