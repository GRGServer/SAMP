CreateGlobalTextDraws()
{
	print("* Creating server wide TextDraws...");
	textDrawClock = TextDrawCreate(547, 25, "_");
	Komma = TextDrawCreate(608.000000,82.000000,",");
	TextDrawSetShadow(textDrawClock, 0);
	TextDrawSetOutline(textDrawClock, 2);
	TextDrawLetterSize(textDrawClock, 0.6, 1.8);
	TextDrawFont(textDrawClock, 3);
	TextDrawAlignment(Komma,3);
	TextDrawBackgroundColor(Komma,0x000000ff);
	TextDrawFont(Komma,0);
	TextDrawLetterSize(Komma,1.100000,1.900000);
	TextDrawColor(Komma,0x00ff0033);
	TextDrawSetOutline(Komma,1);
	TextDrawSetProportional(Komma,1);
	TextDrawSetShadow(Komma,1);
	//Ladebalken
	for(new playerid = 0; playerid < MAX_PLAYERS; playerid++)
    {
		Food[playerid] = TextDrawCreate(502.000000,110.000000,"Food: ~g~lllllllllllllll");
		TextDrawBackgroundColor(Food[playerid], 255);
		TextDrawFont(Food[playerid], 1);
		TextDrawLetterSize(Food[playerid], 0.500000, 1.599999);
		TextDrawColor(Food[playerid], -1);
		TextDrawSetOutline(Food[playerid], 0);
		TextDrawSetProportional(Food[playerid], 1);
		TextDrawSetShadow(Food[playerid], 1);
		IsFoodFull[playerid] = 100;		
		Drink[playerid] = TextDrawCreate(502.000000,125.000000,"Drink: ~g~lllllllllllllll");
		TextDrawBackgroundColor(Drink[playerid], 255);
		TextDrawFont(Drink[playerid], 1);
		TextDrawLetterSize(Drink[playerid], 0.500000, 1.599999);
		TextDrawColor(Drink[playerid], -1);
		TextDrawSetOutline(Drink[playerid], 0);
		TextDrawSetProportional(Drink[playerid], 1);
		TextDrawSetShadow(Drink[playerid], 1);
		IsDrinkFull[playerid] = 100;
		Pee[playerid] = TextDrawCreate(502.000000,140.000000,"Pee: ~g~lllllllllllllll");
		TextDrawBackgroundColor(Pee[playerid], 255);
		TextDrawFont(Pee[playerid], 1);
		TextDrawLetterSize(Pee[playerid], 0.500000, 1.599999);
		TextDrawColor(Pee[playerid], -1);
		TextDrawSetOutline(Pee[playerid], 0);
		TextDrawSetProportional(Pee[playerid], 1);
		TextDrawSetShadow(Pee[playerid], 1);
		IsPeeFull[playerid] = 100;
    }
    for(new i; i < MAX_PLAYERS; i ++)
    {
        if(IsPlayerConnected(i))
        {
            TextDrawShowForPlayer(i, Food[i]);
        }
    }
}