ShowDialog:Service(playerID)
{
	FormatNew:title[20](LanguageString(playerID, 577));
	new options[1024];
	AddLine(options, LanguageString(playerID, 578));// Item 1
	AddLine(options, LanguageString(playerID, 579));// Item 2
	AddLine(options, LanguageString(playerID, 580));// Item 3
	AddLine(options, LanguageString(playerID, 581));// Item 4
	CreateDialog(playerID, "Service", DIALOG_STYLE_LIST, title, options, LanguageString(playerID, 164), LanguageString(playerID, 165));
}

DialogResponse:Service(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0:
			{
				SendClientMessageEx(playerID, COLOR_INFO, 582);
			}
			case 1:
			{
				SendClientMessageEx(playerID, COLOR_INFO, 582);
			}
			case 2:
			{
				SendClientMessageEx(playerID, COLOR_INFO, 582);
			}
			case 3: 
			{
				SendClientMessageEx(playerID, COLOR_INFO, 582);
			}
		}
	}
}