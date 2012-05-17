ShowDialog:FunAction(playerID)
{
	FormatNew:string[1024]("Stop\n");
	Format:string("%s\nDance 1\nDance 2\nDance 3\nDance 4", string);
	Format:string("%s\nHands Up\nSitting", string);
	Format:string("%s\nDrink Beer\nSmoke Ciggy\nDrink Wine\nDrink Sprunk", string);
	Format:string("%s\nPissing", string);
	CreateDialog(playerID, "FunAction", DIALOG_STYLE_LIST, "Fun Action", string, "OK", LanguageString(playerID, 165));
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
			case 6:// Setting
				action = SPECIAL_ACTION_SITTING;
			case 7:// Drink Beer
				action = SPECIAL_ACTION_DRINK_BEER;
			case 8:// Smoke Ciggy
				action = SPECIAL_ACTION_SMOKE_CIGGY;
			case 9:// Drink Wine
				action = SPECIAL_ACTION_DRINK_WINE;
			case 10:// Drink Sprunk
				action = SPECIAL_ACTION_DRINK_SPRUNK;
			case 11:// Pissing
				action = SPECIAL_ACTION_PISSING;
		}
		SetPlayerSpecialAction(playerID, action);
	}
}