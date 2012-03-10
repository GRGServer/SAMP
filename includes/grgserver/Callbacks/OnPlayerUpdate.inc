public OnPlayerUpdate(playerid)
{
	if (PVar:playerid[PAYDAY])
	{
		PVar:playerid[PAYDAY] = false;
		PayDay(playerid);
	}
	if (PVar:playerid[SAVENOW])
	{
		PVar:playerid[SAVENOW] = false;
		SavePlayer(playerid);
	}
	return true;
}