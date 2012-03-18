ReloadTextDraws(playerID)
{
	if (PTextDraw:playerID[VEHICLENAME])
	{
		TextDrawDestroy(PTextDraw:playerID[VEHICLENAME]);
	}
	PTextDraw:playerID[VEHICLENAME] = TextDrawCreate(480, 385, "_");
	TextDrawAlignment(PTextDraw:playerID[VEHICLENAME], 1);
	TextDrawLetterSize(PTextDraw:playerID[VEHICLENAME], 0.3, 0.9);
	TextDrawFont(PTextDraw:playerID[VEHICLENAME], 1);
	TextDrawSetShadow(PTextDraw:playerID[VEHICLENAME], 2);
	if (PTextDraw:playerID[SPEEDO_COLUMN1])
	{
		TextDrawDestroy(PTextDraw:playerID[SPEEDO_COLUMN1]);
	}
	PTextDraw:playerID[SPEEDO_COLUMN1] = TextDrawCreate(480, 385, LanguageString(playerID, 160));
	TextDrawAlignment(PTextDraw:playerID[SPEEDO_COLUMN1], 1);
	TextDrawLetterSize(PTextDraw:playerID[SPEEDO_COLUMN1], 0.3, 0.9);
	TextDrawFont(PTextDraw:playerID[SPEEDO_COLUMN1], 1);
	TextDrawSetShadow(PTextDraw:playerID[SPEEDO_COLUMN1], 2);
	TextDrawTextSize(PTextDraw:playerID[SPEEDO_COLUMN1], 635, 455);
	TextDrawBoxColor(PTextDraw:playerID[SPEEDO_COLUMN1], 0x00000080);
	TextDrawUseBox(PTextDraw:playerID[SPEEDO_COLUMN1], true);
	if (PTextDraw:playerID[SPEEDO_COLUMN2])
	{
		TextDrawDestroy(PTextDraw:playerID[SPEEDO_COLUMN2]);
	}
	PTextDraw:playerID[SPEEDO_COLUMN2] = TextDrawCreate(580, 385, "_");
	TextDrawAlignment(PTextDraw:playerID[SPEEDO_COLUMN2], 1);
	TextDrawLetterSize(PTextDraw:playerID[SPEEDO_COLUMN2], 0.3, 0.9);
	TextDrawFont(PTextDraw:playerID[SPEEDO_COLUMN2], 1);
	TextDrawSetShadow(PTextDraw:playerID[SPEEDO_COLUMN2], 2);
	if (PTextDraw:playerID[RADIOSTATION])
	{
		TextDrawDestroy(PTextDraw:playerID[RADIOSTATION]);
	}
	PTextDraw:playerID[RADIOSTATION] = TextDrawCreate(320, 20, "_");
	TextDrawAlignment(PTextDraw:playerID[RADIOSTATION], 2);
	TextDrawBackgroundColor(PTextDraw:playerID[RADIOSTATION], 0x000000ff);
	TextDrawFont(PTextDraw:playerID[RADIOSTATION], 2);
	TextDrawLetterSize(PTextDraw:playerID[RADIOSTATION], 0.4, 1.6);
	TextDrawColor(PTextDraw:playerID[RADIOSTATION], 0x906010ff);
	TextDrawSetOutline(PTextDraw:playerID[RADIOSTATION], 1);
	TextDrawSetProportional(PTextDraw:playerID[RADIOSTATION], 2);
	TextDrawSetShadow(PTextDraw:playerID[RADIOSTATION], 1);
}