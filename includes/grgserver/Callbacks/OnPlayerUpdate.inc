public OnPlayerUpdate(playerid)
{
	if (savePlayers[playerid])
	{
		SavePlayer(playerid);
		savePlayers[playerid] = false;
	}
	return true;
}