ShowDialog:Police_Options(playerID)
{
	FormatNew:options[70]("Aufträge");
	Format:options("%s\nFinazen", options);
	Format:options("%s\nBewerbungsübersicht", options);
	Format:options("%s\nKündigen", options);
	Format:options("%s\nBetreten", options);
	CreateDialog(playerID, "Police_Options", DIALOG_STYLE_LIST, "Polizei", options, "OK", LanguageString(playerID, 165));
}

DialogResponse:Police_Options(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0: // Accept jobs
			{
				ShowDialog:Accept(playerID);
			}
			case 1: // Finanzen
			{
				SendClientMessage(playerID, COLOR_SYSTEM, "Work in progress");
			}
			case 2: // Applications overview
			{
				SendClientMessage(playerID, COLOR_SYSTEM, "Work in progress");
			}
			case 3: // Cancel job
			{
				SendClientMessage(playerID, COLOR_SYSTEM, "Work in progress");
			}
			case 4: // Enter
			{
				SendClientMessage(playerID, COLOR_SYSTEM, "Work in progress");
			}
		}
	}
}