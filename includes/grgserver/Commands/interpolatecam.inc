PCMD:interpolatecam[ADMIN](playerID, params[], 0)
{
	if (fexist("interpolatecam.txt"))
	{
		new File:file = fopen("interpolatecam.txt", io_read);
		if (file)
		{
			new string[256];
			new Float:startPosX;
			new Float:startPosY;
			new Float:startPosZ;
			new Float:endPosX;
			new Float:endPosY;
			new Float:endPosZ;
			new Float:startLookX;
			new Float:startLookY;
			new Float:startLookZ;
			new Float:endLookX;
			new Float:endLookY;
			new Float:endLookZ;
			new time;
			new cutType;
			fread(file, string);
			if (sscanf(string, "p,ffffff", startPosX, startPosY, startPosZ, endPosX, endPosY, endPosZ))
			{
				SendClientMessage(playerID, COLOR_ERROR, "Incorrect file format for position!");
				return COMMAND_ERROR;
			}
			fread(file, string);
			if (sscanf(string, "p,ffffff", startLookX, startLookY, startLookZ, endLookX, endLookY, endLookZ))
			{
				SendClientMessage(playerID, COLOR_ERROR, "Incorrect file format for look at!");
				return COMMAND_ERROR;
			}
			fread(file, string);
			if (sscanf(string, "p,dd", time, cutType))
			{
				SendClientMessage(playerID, COLOR_ERROR, "Incorrect file format for misc parameters!");
				return COMMAND_ERROR;
			}
			InterpolateCameraPos(playerID, startPosX, startPosY, startPosZ, endPosX, endPosY, endPosZ, time, cutType);
			InterpolateCameraLookAt(playerID, startLookX, startLookY, startLookZ, endLookX, endLookY, endLookZ, time, cutType);
			fclose(file);
			return COMMAND_OK;
		}
	}
	return COMMAND_ERROR;
}