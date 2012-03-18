Teleport(playerID, Float:posX, Float:posY, Float:posZ, Float:angle, interior, virtualWorld)
{
	if (TeleportTo(playerID, posX, posY, posZ, angle, interior, virtualWorld))
	{
		return true;
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 136);
		return false;
	}
}