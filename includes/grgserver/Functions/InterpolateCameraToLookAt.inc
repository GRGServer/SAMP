InterpolateCameraToLookAt(playerID, Float:posX, Float:posY, Float:posZ, time, cut = CAMERA_CUT)
{
	InterpolateCameraLookAt(playerID, PVar:playerID[CAMERA_LOOKX], PVar:playerID[CAMERA_LOOKY], PVar:playerID[CAMERA_LOOKZ], posX, posY, posZ, time, cut);
	PVar:playerID[CAMERA_LOOKX] = posX;
	PVar:playerID[CAMERA_LOOKY] = posY;
	PVar:playerID[CAMERA_LOOKZ] = posZ;
}