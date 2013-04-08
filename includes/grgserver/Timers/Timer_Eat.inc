Timer:Eat(playerid)
{
	if(IsFoodFull[playerid] == 100)
	{
		TextDrawSetString(Food[playerid],"Food: ~g~llllllllllllll");
		IsFoodFull[playerid] = 90;
	}
	if(IsFoodFull[playerid] == 90)
	{
		TextDrawSetString(Food[playerid],"Food: ~g~lllllllllllll");
		IsFoodFull[playerid] = 80;
	}
	if(IsFoodFull[playerid] == 80)
	{
		TextDrawSetString(Food[playerid],"Food: ~g~llllllllllll");
		IsFoodFull[playerid] = 70;
	}
	if(IsFoodFull[playerid] == 70)
	{
		TextDrawSetString(Food[playerid],"Food: ~g~llllllllll");
		IsFoodFull[playerid] = 60;
	}
	if(IsFoodFull[playerid] == 60)
	{
		TextDrawSetString(Food[playerid],"Food: ~g~lllllll");
		IsFoodFull[playerid] = 50;
	}
	if(IsFoodFull[playerid] == 50)
	{
		TextDrawSetString(Food[playerid],"Food: ~y~llllll");
		IsFoodFull[playerid] = 40;
	}
	if(IsFoodFull[playerid] == 40)
	{
		TextDrawSetString(Food[playerid],"Food: ~y~llll");
		IsFoodFull[playerid] = 30;
	}
	if(IsFoodFull[playerid] == 30)
	{
		TextDrawSetString(Food[playerid],"Food: ~r~lll");
		IsFoodFull[playerid] = 20;
	}
	if(IsFoodFull[playerid] == 20)
	{
		TextDrawSetString(Food[playerid],"Food: ~r~ll");
		IsFoodFull[playerid] = 10;
	}
	if(IsFoodFull[playerid] == 10)
	{
		TextDrawSetString(Food[playerid],"Food: ~r~l");
		IsFoodFull[playerid] = 0;
	}
	if(IsFoodFull[playerid] == 0)
	{
		TextDrawSetString(Food[playerid],"Food: ~r~");
		SetPlayerHealth(playerid, 0);
	}
}