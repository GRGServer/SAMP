PCMD:setcam[ADMIN](playerID, params[], 0)
{
	if (fexist("setcam.txt"))
	{
		new File:file = fopen("setcam.txt", io_read);
		if (file)
		{
			new Float:posX;
			new Float:posY;
			new Float:posZ;
			GetPlayerCameraPos(playerID, posX, posY, posZ);
			Timer_PlaySetCam(playerID, file, 1, posX, posY, posZ, 0.0, 0.0, 0.0);
			return COMMAND_OK;
		}
	}
	return COMMAND_ERROR;
}


Timer:PlaySetCam(playerID, File:file, line, Float:startPosX, Float:startPosY, Float:startPosZ, Float:startLookX, Float:startLookY, Float:startLookZ)
{
	new string[256];
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:lookX;
	new Float:lookY;
	new Float:lookZ;
	new time;
	new waitTime;
	if (!fread(file, string))
	{
		SetCameraBehindPlayer(playerID);
		fclose(file);
		return false;
	}
	if (sscanf(string, "p,ffffffdd", posX, posY, posZ, lookX, lookY, lookZ, time, waitTime))
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 388, line);
		fclose(file);
		return false;
	}
	if (startPosX == 0.0 && startPosY == 0.0 && startPosZ == 0.0)
	{
		startPosX = posX;
		startPosY = posY;
		startPosZ = posZ;
	}
	if (startLookX == 0.0 && startLookY == 0.0 && startLookZ == 0.0)
	{
		startLookX = lookX;
		startLookY = lookY;
		startLookZ = lookZ;
	}
	SetTimerEx("Timer_PlaySetCam", time + waitTime, false, "dddffffff", playerID, _:file, line + 1, posX, posY, posZ, lookX, lookY, lookZ);
	InterpolateCameraPos(playerID, startPosX, startPosY, startPosZ, posX, posY, posZ, time, CAMERA_CUT);
	InterpolateCameraLookAt(playerID, startLookX, startLookY, startLookZ, lookX, lookY, lookZ, time, CAMERA_CUT);
	return true;
}