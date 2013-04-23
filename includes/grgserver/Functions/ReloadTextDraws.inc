ReloadTextDraws(playerID)
{
	// Needs

	if (PVar:playerID[PROGRESSBAR_NEEDS_BLADDER])
	{
		DestroyPlayerProgressBar(playerID, PVar:playerID[PROGRESSBAR_NEEDS_BLADDER]);
	}
	PVar:playerID[PROGRESSBAR_NEEDS_BLADDER] = CreatePlayerProgressBar(playerID, 575, 135, 27, 5, 0x006000FF, 100);

	if (PVar:playerID[PROGRESSBAR_NEEDS_ENERGY])
	{
		DestroyPlayerProgressBar(playerID, PVar:playerID[PROGRESSBAR_NEEDS_ENERGY]);
	}
	PVar:playerID[PROGRESSBAR_NEEDS_ENERGY] = CreatePlayerProgressBar(playerID, 575, 146, 27, 5, 0x006000FF, 100);

	if (PVar:playerID[PROGRESSBAR_NEEDS_HUNGER])
	{
		DestroyPlayerProgressBar(playerID, PVar:playerID[PROGRESSBAR_NEEDS_HUNGER]);
	}
	PVar:playerID[PROGRESSBAR_NEEDS_HUNGER] = CreatePlayerProgressBar(playerID, 575, 113, 27, 5, 0x006000FF, 100);

	if (PVar:playerID[PROGRESSBAR_NEEDS_THIRST])
	{
		DestroyPlayerProgressBar(playerID, PVar:playerID[PROGRESSBAR_NEEDS_THIRST]);
	}
	PVar:playerID[PROGRESSBAR_NEEDS_THIRST] = CreatePlayerProgressBar(playerID, 575, 124, 27, 5, 0x006000FF, 100);

	if (PTextDraw:playerID[NEEDS_TEXT])
	{
		PlayerTextDrawDestroy(playerID, PTextDraw:playerID[NEEDS_TEXT]);
	}
	PTextDraw:playerID[NEEDS_TEXT] = CreatePlayerTextDraw(playerID, 500, 110, LanguageString(playerID, StringID:631("")));
	PlayerTextDrawAlignment(playerID, PTextDraw:playerID[NEEDS_TEXT], 1);
	PlayerTextDrawLetterSize(playerID, PTextDraw:playerID[NEEDS_TEXT], 0.3, 1.2);
	PlayerTextDrawFont(playerID, PTextDraw:playerID[NEEDS_TEXT], 1);
	PlayerTextDrawSetShadow(playerID, PTextDraw:playerID[NEEDS_TEXT], 2);
	PlayerTextDrawTextSize(playerID, PTextDraw:playerID[NEEDS_TEXT], 605, 0);
	PlayerTextDrawBoxColor(playerID, PTextDraw:playerID[NEEDS_TEXT], 0x00000080);
	PlayerTextDrawUseBox(playerID, PTextDraw:playerID[NEEDS_TEXT], true);


	// Speedo

	if (PTextDraw:playerID[VEHICLENAME])
	{
		PlayerTextDrawDestroy(playerID, PTextDraw:playerID[VEHICLENAME]);
	}
	PTextDraw:playerID[VEHICLENAME] = CreatePlayerTextDraw(playerID, 480, 385, "_");
	PlayerTextDrawAlignment(playerID, PTextDraw:playerID[VEHICLENAME], 1);
	PlayerTextDrawLetterSize(playerID, PTextDraw:playerID[VEHICLENAME], 0.3, 0.9);
	PlayerTextDrawFont(playerID, PTextDraw:playerID[VEHICLENAME], 1);
	PlayerTextDrawSetShadow(playerID, PTextDraw:playerID[VEHICLENAME], 2);

	if (PTextDraw:playerID[SPEEDO_COLUMN1])
	{
		PlayerTextDrawDestroy(playerID, PTextDraw:playerID[SPEEDO_COLUMN1]);
	}
	PTextDraw:playerID[SPEEDO_COLUMN1] = CreatePlayerTextDraw(playerID, 480, 385, LanguageString(playerID, StringID:160("")));
	PlayerTextDrawAlignment(playerID, PTextDraw:playerID[SPEEDO_COLUMN1], 1);
	PlayerTextDrawLetterSize(playerID, PTextDraw:playerID[SPEEDO_COLUMN1], 0.3, 0.9);
	PlayerTextDrawFont(playerID, PTextDraw:playerID[SPEEDO_COLUMN1], 1);
	PlayerTextDrawSetShadow(playerID, PTextDraw:playerID[SPEEDO_COLUMN1], 2);
	PlayerTextDrawTextSize(playerID, PTextDraw:playerID[SPEEDO_COLUMN1], 635, 0);
	PlayerTextDrawBoxColor(playerID, PTextDraw:playerID[SPEEDO_COLUMN1], 0x00000080);
	PlayerTextDrawUseBox(playerID, PTextDraw:playerID[SPEEDO_COLUMN1], true);

	if (PTextDraw:playerID[SPEEDO_COLUMN2])
	{
		PlayerTextDrawDestroy(playerID, PTextDraw:playerID[SPEEDO_COLUMN2]);
	}
	PTextDraw:playerID[SPEEDO_COLUMN2] = CreatePlayerTextDraw(playerID, 580, 385, "_");
	PlayerTextDrawAlignment(playerID, PTextDraw:playerID[SPEEDO_COLUMN2], 1);
	PlayerTextDrawLetterSize(playerID, PTextDraw:playerID[SPEEDO_COLUMN2], 0.3, 0.9);
	PlayerTextDrawFont(playerID, PTextDraw:playerID[SPEEDO_COLUMN2], 1);
	PlayerTextDrawSetShadow(playerID, PTextDraw:playerID[SPEEDO_COLUMN2], 2);


	if (PTextDraw:playerID[RADIOSTATION])
	{
		PlayerTextDrawDestroy(playerID, PTextDraw:playerID[RADIOSTATION]);
	}
	PTextDraw:playerID[RADIOSTATION] = CreatePlayerTextDraw(playerID, 320, 20, "_");
	PlayerTextDrawAlignment(playerID, PTextDraw:playerID[RADIOSTATION], 2);
	PlayerTextDrawBackgroundColor(playerID, PTextDraw:playerID[RADIOSTATION], 0x000000FF);
	PlayerTextDrawFont(playerID, PTextDraw:playerID[RADIOSTATION], 2);
	PlayerTextDrawLetterSize(playerID, PTextDraw:playerID[RADIOSTATION], 0.4, 1.6);
	PlayerTextDrawColor(playerID, PTextDraw:playerID[RADIOSTATION], 0x906010ff);
	PlayerTextDrawSetOutline(playerID, PTextDraw:playerID[RADIOSTATION], 1);
	PlayerTextDrawSetProportional(playerID, PTextDraw:playerID[RADIOSTATION], 2);
	PlayerTextDrawSetShadow(playerID, PTextDraw:playerID[RADIOSTATION], 1);


	// Misc

	if (PTextDraw:playerID[SCREENFADER])
	{
		PlayerTextDrawDestroy(playerID, PTextDraw:playerID[SCREENFADER]);
	}
	PTextDraw:playerID[SCREENFADER] = CreatePlayerTextDraw(playerID, 0, 0, "~r~");
	PlayerTextDrawLetterSize(playerID, PTextDraw:playerID[SCREENFADER], 0, 50);
	PlayerTextDrawUseBox(playerID, PTextDraw:playerID[SCREENFADER], true);

	if (PTextDraw:playerID[SHOWPOS])
	{
		PlayerTextDrawDestroy(playerID, PTextDraw:playerID[SHOWPOS]);
	}
	PTextDraw:playerID[SHOWPOS] = CreatePlayerTextDraw(playerID, 10, 140, "_");
	PlayerTextDrawLetterSize(playerID, PTextDraw:playerID[SHOWPOS], 0.5, 1.2);
	PlayerTextDrawFont(playerID, PTextDraw:playerID[SHOWPOS], 2);
	PlayerTextDrawSetShadow(playerID, PTextDraw:playerID[SHOWPOS], 0);
	PlayerTextDrawSetOutline(playerID, PTextDraw:playerID[SHOWPOS], 1);
}