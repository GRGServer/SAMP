Teleport(playerID, Float:posX, Float:posY, Float:posZ, Float:angle, interior, virtualWorld)
{
	if (TeleportTo(playerID, posX, posY, posZ, angle, interior, virtualWorld))
	{
		return true;
	}
	else
	{
		SendClientMessage(playerID, COLOR_ERROR, "Beim Teleportieren ist ein Fehler aufgetreten! Bitte versuche es erneut.");
		return false;
	}
}