Timer:FlyCam(playerID)
{
	new keys;
	new updown;
	new leftright;
	new Float:speed = FLYCAM_SPEED_NORMAL;
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:vectorX;
	new Float:vectorY;
	new Float:vectorZ;
	new Float:angle;
	new Float:angleElevation;
	GetPlayerKeys(playerID, keys, updown, leftright);
	GetPlayerCameraPos(playerID, posX, posY, posZ);
	GetPlayerCameraFrontVector(playerID, vectorX, vectorY, vectorZ);
	angle = 90 - atan2(vectorY, vectorX);
	if (angle < 0.0)
	{
		angle = 360.0 + angle;
	}
	angleElevation = - (floatabs(atan2(floatsqroot(floatpower(vectorX, 2.0) + floatpower(vectorY, 2.0)), vectorZ)) - 90.0);
	if (keys & KEY_JUMP)
	{
		speed = FLYCAM_SPEED_FAST;
	}
	if (keys & KEY_WALK)
	{
		speed = FLYCAM_SPEED_SLOW;
	}
	if (updown == KEY_UP)
	{
		GetXYZFromAngle(posX, posY, posZ, angle, angleElevation, 50.0);
		MoveDynamicObject(PVar:playerID[FLYCAM_DUMMYOBJECT], posX, posY, posZ, speed);
	}
	if (updown == KEY_DOWN)
	{
		GetXYZFromAngle(posX, posY, posZ, angle, angleElevation, -50.0);
		MoveDynamicObject(PVar:playerID[FLYCAM_DUMMYOBJECT], posX, posY, posZ, speed);
	}
	if (leftright == KEY_LEFT)
	{
		GetXYFromAngle(posX, posY, -angle + 90.0, 50.0);
		MoveDynamicObject(PVar:playerID[FLYCAM_DUMMYOBJECT], posX, posY, posZ, speed);
	}
	if (leftright == KEY_RIGHT)
	{
		GetXYFromAngle(posX, posY, -angle + 90.0, -50.0);
		MoveDynamicObject(PVar:playerID[FLYCAM_DUMMYOBJECT], posX, posY, posZ, speed);
	}
	if (keys & KEY_SPRINT)
	{
		MoveDynamicObject(PVar:playerID[FLYCAM_DUMMYOBJECT], posX, posY, posZ + 50.0, speed);
	}
	if (keys & KEY_CROUCH)
	{
		MoveDynamicObject(PVar:playerID[FLYCAM_DUMMYOBJECT], posX, posY, posZ - 50.0, speed);
	}
	if (!(updown & KEY_UP || updown & KEY_DOWN || leftright & KEY_LEFT || leftright & KEY_RIGHT || keys & KEY_SPRINT || keys & KEY_CROUCH))
	{
		StopDynamicObject(PVar:playerID[FLYCAM_DUMMYOBJECT]);
	}
}