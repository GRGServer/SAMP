CreateGlobalTextDraws()
{
	print("* Creating server wide TextDraws...");
	textDrawSpeedoColumn1 = TextDrawCreate(480, 385, "~n~Geschwindigkeit:~n~Zustand:~n~Tank:~n~Verbrauch/100km:");
	TextDrawAlignment(textDrawSpeedoColumn1, 1);
	TextDrawLetterSize(textDrawSpeedoColumn1, 0.3, 0.9);
	TextDrawFont(textDrawSpeedoColumn1, 1);
	TextDrawSetShadow(textDrawSpeedoColumn1, 2);
	TextDrawTextSize(textDrawSpeedoColumn1, 635, 455);
	TextDrawBoxColor(textDrawSpeedoColumn1, 0x00000080);
	TextDrawUseBox(textDrawSpeedoColumn1, true);
	textDrawClock = TextDrawCreate(547, 25, "_");
	TextDrawSetShadow(textDrawClock, 0);
	TextDrawSetOutline(textDrawClock, 2);
	TextDrawLetterSize(textDrawClock, 0.6, 1.8);
	TextDrawFont(textDrawClock, 3);
}