public OnPlayerRequestClass(playerid, classid)
{
	SetTimerEx("Timer_SpawnPlayer", 200, false, "d", playerid);
	return true;
}