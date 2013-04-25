GetPlayerZone(playerID, checkZ)
{
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	GetPlayerPos(playerID, posX, posY, posZ);
	Count(zone, sizeof(zones))
	{
		if (posX >= zones[zone][ZONE_STARTX] && posX <= zones[zone][ZONE_ENDX] && posY >= zones[zone][ZONE_STARTY] && posY <= zones[zone][ZONE_ENDY])
		{
			if (!checkZ || (posZ >= zones[zone][ZONE_STARTZ] && posZ <= zones[zone][ZONE_ENDZ]))
			{
				return zone;
			}
		}
	}
	return -1;
}