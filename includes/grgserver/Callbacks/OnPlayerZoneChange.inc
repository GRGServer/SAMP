OnPlayerZoneChange(playerID, zone)
{
	GameTextForPlayer(playerID, zones[zone][ZONE_NAME], 2000, 3);
}