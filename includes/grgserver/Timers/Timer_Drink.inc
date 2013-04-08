Timer:Drink(playerid)
{
	if(IsDrinkFull[playerid] == 100)
	{
		TextDrawSetString(Drink[playerid],"Drink: ~g~llllllllllllll");
		IsDrinkFull[playerid] = 90;
	}
	if(IsDrinkFull[playerid] == 90)
	{
		TextDrawSetString(Drink[playerid],"Drink: ~g~lllllllllllll");
		IsDrinkFull[playerid] = 80;
	}
	if(IsDrinkFull[playerid] == 80)
	{
		TextDrawSetString(Drink[playerid],"Drink: ~g~llllllllllll");
		IsDrinkFull[playerid] = 70;
	}
	if(IsDrinkFull[playerid] == 70)
	{
		TextDrawSetString(Drink[playerid],"Drink: ~g~llllllllll");
		IsDrinkFull[playerid] = 60;
	}
	if(IsDrinkFull[playerid] == 60)
	{
		TextDrawSetString(Drink[playerid],"Drink: ~g~lllllll");
		IsDrinkFull[playerid] = 50;
	}
	if(IsDrinkFull[playerid] == 50)
	{
		TextDrawSetString(Drink[playerid],"Drink: ~y~llllll");
		IsDrinkFull[playerid] = 40;
	}
	if(IsDrinkFull[playerid] == 40)
	{
		TextDrawSetString(Drink[playerid],"Drink: ~y~llll");
		IsDrinkFull[playerid] = 30;
	}
	if(IsDrinkFull[playerid] == 30)
	{
		TextDrawSetString(Drink[playerid],"Drink: ~r~lll");
		IsDrinkFull[playerid] = 20;
	}
	if(IsDrinkFull[playerid] == 20)
	{
		TextDrawSetString(Drink[playerid],"Drink: ~r~ll");
		IsDrinkFull[playerid] = 10;
	}
	if(IsDrinkFull[playerid] == 10)
	{
		TextDrawSetString(Drink[playerid],"Drink: ~r~l");
		IsDrinkFull[playerid] = 0;
	}
	if(IsDrinkFull[playerid] == 0)
	{
		TextDrawSetString(Drink[playerid],"Drink: ~r~");
		SetPlayerHealth(playerid, 0);
	}
}