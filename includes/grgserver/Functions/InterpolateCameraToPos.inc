InterpolateCameraToPos(playerID, Float:posX, Float:posY, Float:posZ, time, cut = CAMERA_CUT)
{
	new Float:startPosX;
	new Float:startPosY;
	new Float:startPosZ;
	GetPlayerCameraPos(playerID, startPosX, startPosY, startPosZ);
	InterpolateCameraPos(playerID, startPosX, startPosY, startPosZ, posX, posY, posZ, time, cut);
}