ShowDialog:TRUCKER_OPTIONS(playerID)
{
	FormatNew:options[50]("Aufträge");
	Format:options("%s\nFinanzen", options);
	Format:options("%s\nKündigen", options);
	Format:options("%s\nBewerbungsübersicht", options);
	CreateDialog(playerID, "TRUCKER_OPTIONS", DIALOG_STYLE_LIST, "Trucker Übersicht", options, "OK", LanguageString(playerID, 165));
}

DialogResponse:TRUCKER_OPTIONS(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0: // Aufträge
			{
				ShowDialog:ACCEPT(playerID);
			}
			case 1: // Finanzen
			{
				// TODO: Finanzen für jeden Job erstellen: Job Guthaben
				SendClientMessage(playerID, COLOR_SYSTEM, "Work in progress");
			}
			case 2: // Kündigen
			{
				SendClientMessage(playerID, COLOR_SYSTEM, "Work in progress");
			}
			case 3: // Bewerbungs übersicht
			{
				SendClientMessage(playerID, COLOR_SYSTEM, "Work in progress");
			}
		}
	}
}