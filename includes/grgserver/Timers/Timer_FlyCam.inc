Timer:FlyCam(playerID)
{
	new keys;
	new updown;
	new leftright;
	GetPlayerKeys(playerID, keys, updown, leftright);
	if (leftright == KEY_LEFT)
	{
		PVar:playerID[FLYCAM_POSX] = floatsub(PVar:playerID[FLYCAM_POSX], 1);
	}
	else if (leftright == KEY_RIGHT)
	{
		PVar:playerID[FLYCAM_POSX] = floatadd(PVar:playerID[FLYCAM_POSX], 1);
	}
	if (updown == KEY_UP)
	{
		PVar:playerID[FLYCAM_POSY] = floatadd(PVar:playerID[FLYCAM_POSY], 1);
	}
	else if (updown == KEY_DOWN)
	{
		PVar:playerID[FLYCAM_POSY] = floatsub(PVar:playerID[FLYCAM_POSY], 1);
	}
	if (keys & KEY_JUMP)
	{
		PVar:playerID[FLYCAM_POSZ] = floatadd(PVar:playerID[FLYCAM_POSZ], 1);
	}
	else if (keys & KEY_SPRINT)
	{
		PVar:playerID[FLYCAM_POSZ] = floatsub(PVar:playerID[FLYCAM_POSZ], 1);
	}
	SetPlayerCameraPos(playerID, PVar:playerID[FLYCAM_POSX], PVar:playerID[FLYCAM_POSY], PVar:playerID[FLYCAM_POSZ]);
	SetPlayerPos(playerID, PVar:playerID[FLYCAM_POSX], PVar:playerID[FLYCAM_POSY], PVar:playerID[FLYCAM_POSZ]);
}