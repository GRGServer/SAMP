ReloadTextDraws(playerID)
{
	if (PTextDraw:playerID[NEEDS_COLUMN1])
	{
		PlayerTextDrawDestroy(playerID, PTextDraw:playerID[NEEDS_COLUMN1]);
	}
	PTextDraw:playerID[NEEDS_COLUMN1] = CreatePlayerTextDraw(playerID, 500, 110, LanguageString(playerID, 631));
	PlayerTextDrawAlignment(playerID, PTextDraw:playerID[NEEDS_COLUMN1], 1);
	PlayerTextDrawLetterSize(playerID, PTextDraw:playerID[NEEDS_COLUMN1], 0.4, 1.2);
	PlayerTextDrawFont(playerID, PTextDraw:playerID[NEEDS_COLUMN1], 1);
	PlayerTextDrawSetShadow(playerID, PTextDraw:playerID[NEEDS_COLUMN1], 2);
	PlayerTextDrawTextSize(playerID, PTextDraw:playerID[NEEDS_COLUMN1], 605, 455);
	PlayerTextDrawBoxColor(playerID, PTextDraw:playerID[NEEDS_COLUMN1], 0x00000080);
	PlayerTextDrawUseBox(playerID, PTextDraw:playerID[NEEDS_COLUMN1], true);

	if (PTextDraw:playerID[NEEDS_COLUMN2])
	{
		PlayerTextDrawDestroy(playerID, PTextDraw:playerID[NEEDS_COLUMN2]);
	}
	PTextDraw:playerID[NEEDS_COLUMN2] = CreatePlayerTextDraw(playerID, 575, 110, "_");
	PlayerTextDrawAlignment(playerID, PTextDraw:playerID[NEEDS_COLUMN2], 1);
	PlayerTextDrawLetterSize(playerID, PTextDraw:playerID[NEEDS_COLUMN2], 0.4, 1.2);
	PlayerTextDrawFont(playerID, PTextDraw:playerID[NEEDS_COLUMN2], 1);
	PlayerTextDrawSetShadow(playerID, PTextDraw:playerID[NEEDS_COLUMN2], 2);

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
	PTextDraw:playerID[SPEEDO_COLUMN1] = CreatePlayerTextDraw(playerID, 480, 385, LanguageString(playerID, 160));
	PlayerTextDrawAlignment(playerID, PTextDraw:playerID[SPEEDO_COLUMN1], 1);
	PlayerTextDrawLetterSize(playerID, PTextDraw:playerID[SPEEDO_COLUMN1], 0.3, 0.9);
	PlayerTextDrawFont(playerID, PTextDraw:playerID[SPEEDO_COLUMN1], 1);
	PlayerTextDrawSetShadow(playerID, PTextDraw:playerID[SPEEDO_COLUMN1], 2);
	PlayerTextDrawTextSize(playerID, PTextDraw:playerID[SPEEDO_COLUMN1], 635, 455);
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
	PlayerTextDrawBackgroundColor(playerID, PTextDraw:playerID[RADIOSTATION], 0x000000ff);
	PlayerTextDrawFont(playerID, PTextDraw:playerID[RADIOSTATION], 2);
	PlayerTextDrawLetterSize(playerID, PTextDraw:playerID[RADIOSTATION], 0.4, 1.6);
	PlayerTextDrawColor(playerID, PTextDraw:playerID[RADIOSTATION], 0x906010ff);
	PlayerTextDrawSetOutline(playerID, PTextDraw:playerID[RADIOSTATION], 1);
	PlayerTextDrawSetProportional(playerID, PTextDraw:playerID[RADIOSTATION], 2);
	PlayerTextDrawSetShadow(playerID, PTextDraw:playerID[RADIOSTATION], 1);

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