ShowDialog:FunAction(playerID)
{
	new options[1024];
	AddLine(options, "Stop");
	AddLine(options, "Dance 1");
	AddLine(options, "Dance 2");
	AddLine(options, "Dance 3");
	AddLine(options, "Dance 4");
	AddLine(options, "Hands Up");
	AddLine(options, "Drink Beer");
	AddLine(options, "Drink Sprunk");
	AddLine(options, "Drink Wine");
	AddLine(options, "Smoke Ciggy");
	AddLine(options, "Pissing");
	CreateDialog(playerID, "FunAction", DIALOG_STYLE_LIST, "Fun Action", options, "OK", LanguageString(playerID, 165));
}

DialogResponse:FunAction(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new action;
		switch (listItem)
		{
			case 0:// Stop
				action = SPECIAL_ACTION_NONE;
			case 1:// Dance 1
				action = SPECIAL_ACTION_DANCE1;
			case 2:// Dance 2
				action = SPECIAL_ACTION_DANCE2;
			case 3:// Dance 3
				action = SPECIAL_ACTION_DANCE3;
			case 4:// Dance 4
				action = SPECIAL_ACTION_DANCE4;
			case 5:// Hands Up
				action = SPECIAL_ACTION_HANDSUP;
			case 6:// Drink Beer
				action = SPECIAL_ACTION_DRINK_BEER;
			case 7:// Drink Sprunk
				action = SPECIAL_ACTION_DRINK_SPRUNK;
			case 8:// Drink Wine
				action = SPECIAL_ACTION_DRINK_WINE;
			case 9:// Smoke Ciggy
				action = SPECIAL_ACTION_SMOKE_CIGGY;
			case 10:// Pissing
				action = SPECIAL_ACTION_PISSING;
		}
		SetPlayerSpecialAction(playerID, action);
	}
}