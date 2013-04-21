PCMD:addspeedcam[MAPPER](playerID, params[], 486)
{
	new speedLimit;
	if (sscanf(params, "d", speedLimit))
	{
		CmdUsageMsg(playerID, "addspeedcam", "SpeedLimit");
		return COMMAND_USAGE;
	}

	new speedCamerasSlot = -1;
	Foreach(arrayIndex, speedCameras)
	{
		if (!speedCameras[arrayIndex][SPEEDCAMERA_OBJECTID])
		{
			speedCamerasSlot = arrayIndex;
			break;
		}
	}

	if (speedCamerasSlot == -1)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, "SPEEDCAMERA_NOFREESLOTFOUND", sizeof(speedCameras));
		return COMMAND_ERROR;
	}

	new objectID = AddObject(playerID, SPEEDCAMERA_OBJECTMODEL, "speedcameras");
	if (objectID)
	{
		speedCameras[speedCamerasSlot][SPEEDCAMERA_OBJECTID] = objectID;
		speedCameras[speedCamerasSlot][SPEEDCAMERA_SPEEDLIMIT] = speedLimit;

		SaveObjects("speedcameras");

		return COMMAND_OK;
	}

	return COMMAND_ERROR;
}