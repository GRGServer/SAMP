Timer:Pee(playerid)
{
	if(IsPeeFull[playerid] == 100)
	{
		TextDrawSetString(Pee[playerid],"Pee: ~g~llllllllllllll");
		IsPeeFull[playerid] = 90;
	}
	if(IsPeeFull[playerid] == 90)
	{
		TextDrawSetString(Pee[playerid],"Pee: ~g~lllllllllllll");
		IsPeeFull[playerid] = 80;
	}
	if(IsPeeFull[playerid] == 80)
	{
		TextDrawSetString(Pee[playerid],"Pee: ~g~llllllllllll");
		IsPeeFull[playerid] = 70;
	}
	if(IsPeeFull[playerid] == 70)
	{
		TextDrawSetString(Pee[playerid],"Pee: ~g~llllllllll");
		IsPeeFull[playerid] = 60;
	}
	if(IsPeeFull[playerid] == 60)
	{
		TextDrawSetString(Pee[playerid],"Pee: ~g~lllllll");
		IsPeeFull[playerid] = 50;
	}
	if(IsPeeFull[playerid] == 50)
	{
		TextDrawSetString(Pee[playerid],"Pee: ~y~llllll");
		IsPeeFull[playerid] = 40;
	}
	if(IsPeeFull[playerid] == 40)
	{
		TextDrawSetString(Pee[playerid],"Pee: ~y~llll");
		IsPeeFull[playerid] = 30;
	}
	if(IsPeeFull[playerid] == 30)
	{
		TextDrawSetString(Pee[playerid],"Pee: ~r~lll");
		IsPeeFull[playerid] = 20;
	}
	if(IsPeeFull[playerid] == 20)
	{
		TextDrawSetString(Pee[playerid],"Pee: ~r~ll");
		IsPeeFull[playerid] = 10;
	}
	if(IsPeeFull[playerid] == 10)
	{
		TextDrawSetString(Pee[playerid],"Pee: ~r~l");
		IsPeeFull[playerid] = 0;
	}
	if(IsPeeFull[playerid] == 0)
	{
		TextDrawSetString(Pee[playerid],"Pee: ~r~");
		SetPlayerHealth(playerid, 0);
	}
}