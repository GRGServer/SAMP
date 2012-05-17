ShowDialog:Police_Job(playerID)
{
	FormatNew:options[60]("Polizeirevier kaufen");
	Format:options("%s\nBewerben", options);
	Format:options("%s\nBetreten", options);
	CreateDialog(playerID, "Police_Job", DIALOG_STYLE_LIST, "Polizei", options, "OK", LanguageString(playerID, 165));
}

DialogResponse:Police_Job(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0: // Buy police
			{
				SendClientMessage(playerID, COLOR_SYSTEM, "Work in progress");
			}
			case 1: // Apply to police
			{
				if(PVar:playerID[JOBID] >= 0)
				{
					SendClientMessage(playerID, COLOR_SYSTEM, "Work in progress");
				}
				else
				{
					SendClientMessageEx(playerID, COLOR_ERROR, 39);
				}
			}
			case 2: // Enter
			{
				SendClientMessage(playerID, COLOR_SYSTEM, "Work in progress");
			}
		}
	}
}