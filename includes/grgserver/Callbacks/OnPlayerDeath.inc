public OnPlayerDeath(playerid, killerid, reason)
{
	SendDeathMessage(killerid, playerid, reason);
	PVar:playerid[DEATHS]++;
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:cameraPosX;
	new Float:cameraPosY;
	new Float:cameraPosZ;
	GetPlayerPos(playerid, posX, posY, posZ);
	GetPlayerCameraPos(playerid, cameraPosX, cameraPosY, cameraPosZ);
	TogglePlayerSpectating(playerid, true);
	SetPlayerCameraLookAt(playerid, posX, posY, posZ);
	InterpolateCameraPos(playerid, cameraPosX, cameraPosY, cameraPosZ, cameraPosX, cameraPosY, cameraPosZ + 10, 10000, CAMERA_CUT);
	if (PVar:playerid[INTUTORIAL])
	{
		StartScreenFader(playerid, 0, 0, 0, 5, 0, FADE_DEATH, 0);
		PVar:playerid[SPAWNAFTERDEATH] = true;
	}
	else
	{
		new closestHospital = GetClosestPickup(playerid, "HOSPITAL");
		StartScreenFader(playerid, 100, 0, 0, 5, 0, FADE_DEATH, 0);
		PVar:playerid[SPAWNAFTERDEATH] = closestHospital;
	}
}