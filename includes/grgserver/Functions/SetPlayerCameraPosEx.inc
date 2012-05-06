SetPlayerCameraLookAtEx(playerID, Float:posX, Float:posY, Float:posZ)
{
	PVar:playerID[CAMERA_LOOKX] = posX;
	PVar:playerID[CAMERA_LOOKY] = posY;
	PVar:playerID[CAMERA_LOOKZ] = posZ;
	SetPlayerCameraLookAt(playerID, posX, posY, posZ);
}