ShowDialog:BusLine(playerID)
{
	new options[1024];
	AddLine(options, LanguageString(playerID, 562));
	AddLine(options, LanguageString(playerID, 563));
	AddLine(options, LanguageString(playerID, 564));
	AddLine(options, LanguageString(playerID, 565));
	CreateDialog(playerID, "BusLine", DIALOG_STYLE_LIST, LanguageString(playerID, 561), options, "OK", LanguageString(playerID, 165));
}

DialogResponse:BusLine(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0: // Line 1
			{
				SendClientMessageEx(playerID, COLOR_INFO, 566);
			}
			case 1: // Line 2 
			{
				SendClientMessageEx(playerID, COLOR_INFO, 566);
			}
			case 2: // Line 3
			{
				SendClientMessageEx(playerID, COLOR_INFO, 566);
			}
			case 3: // line 4
			{
				SendClientMessageEx(playerID, COLOR_INFO, 566);
			}
			case 4: // line 5
			{
				SendClientMessageEx(playerID, COLOR_INFO, 566);
			}
		}
	}
}