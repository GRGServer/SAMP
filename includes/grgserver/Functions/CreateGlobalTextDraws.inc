CreateGlobalTextDraws()
{
	print("* Creating server wide TextDraws...");

	decimalPoint = TextDrawCreate(608, 82, ",");
	TextDrawAlignment(decimalPoint, 3);
	TextDrawBackgroundColor(decimalPoint, 0x000000ff);
	TextDrawFont(decimalPoint, 0);
	TextDrawLetterSize(decimalPoint, 1.1, 1.9);
	TextDrawColor(decimalPoint, 0x00ff0033);
	TextDrawSetOutline(decimalPoint, 1);
	TextDrawSetProportional(decimalPoint, 1);
	TextDrawSetShadow(decimalPoint, 1);

	textDrawClock = TextDrawCreate(547, 25, "_");
	TextDrawSetShadow(textDrawClock, 0);
	TextDrawSetOutline(textDrawClock, 2);
	TextDrawLetterSize(textDrawClock, 0.6, 1.8);
	TextDrawFont(textDrawClock, 3);
}