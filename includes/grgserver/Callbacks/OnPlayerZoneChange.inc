OnPlayerZoneChange(playerID, zone)
{
	if (IsLoggedIn(playerID))
	{
		GameTextForPlayer(playerID, zones[zone][ZONE_NAME], 2000, 3);
	}
}