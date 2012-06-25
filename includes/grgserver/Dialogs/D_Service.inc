ShowDialog:Service(playerID)
{
	new options[1024];
	AddLine(options, LanguageString(playerID, 176));// Item 1
	AddLine(options, "ADAC");// Item 2
	AddLine(options, "Taxi");// Item 3
	AddLine(options, LanguageString(playerID, 221));// Item 4
	CreateDialog(playerID, "Service", DIALOG_STYLE_LIST, LanguageString(playerID, 577), options, LanguageString(playerID, 164), LanguageString(playerID, 165));
}

DialogResponse:Service(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0:
			{
				SendClientMessage(playerID, COLOR_SYSTEM, "Coming soon...");
			}
			case 1:
			{
				SendClientMessage(playerID, COLOR_SYSTEM, "Coming soon...");
			}
			case 2:
			{
				SendClientMessage(playerID, COLOR_SYSTEM, "Coming soon...");
			}
			case 3: 
			{
				SendClientMessage(playerID, COLOR_SYSTEM, "Coming soon...");
			}
		}
	}
}