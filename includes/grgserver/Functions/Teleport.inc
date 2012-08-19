Teleport(playerID, Float:posX, Float:posY, Float:posZ, Float:angle, interior, virtualWorld)
{
	PVar:playerID[TELEPORT_POSX] = posX;
	PVar:playerID[TELEPORT_POSY] = posY;
	PVar:playerID[TELEPORT_POSZ] = posZ;
	PVar:playerID[TELEPORT_ANGLE] = angle;
	PVar:playerID[TELEPORT_INTERIOR] = interior;
	PVar:playerID[TELEPORT_VIRTUALWORLD] = virtualWorld;
	TogglePlayerControllable(playerID, false);
	StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_TELEPORT, 0);
}