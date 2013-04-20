ShowDialog:Police_Options(playerID)
{
	FormatNew:title[20](LanguageString(playerID, "553"));
	new options[1024];
	AddLine(options, LanguageString(playerID, "546"));// Item 1
	AddLine(options, LanguageString(playerID, "547"));// Item 2
	AddLine(options, LanguageString(playerID, "548"));// Item 3
	AddLine(options, LanguageString(playerID, "549"));// Item 4
	CreateDialog(playerID, "Police Options", DIALOG_STYLE_LIST, title, options, LanguageString(playerID, "164"), LanguageString(playerID, "165"));
}

DialogResponse:Police_Options(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0:
			{
				SendClientMessage(playerID, COLOR_INFO, "Comming soon....");
			}
			case 1:
			{
				SendClientMessage(playerID, COLOR_INFO, "Comming soon....");
			}
			case 2:
			{
				SendClientMessage(playerID, COLOR_INFO, "Comming soon....");
			}
			case 3: 
			{
				SendClientMessage(playerID, COLOR_INFO, "Comming soon....");
			}
		}
	}
}