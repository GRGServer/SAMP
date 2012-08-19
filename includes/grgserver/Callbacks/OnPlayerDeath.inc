public OnPlayerDeath(playerid, killerid, reason)
{
	new closestHospital = GetClosestPickup(playerid, "HOSPITAL");
	SendDeathMessage(killerid, playerid, reason);
	TogglePlayerControllable(playerid, false);
	StartScreenFader(playerid, 100, 0, 0, 1, 0, FADE_DEATH, 0);
	PVar:playerid[DEATHS] ++;
	PVar:playerid[SPAWNAFTERDEATH] = closestHospital;
}