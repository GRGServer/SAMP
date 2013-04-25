PCMD:addspeedcam[MAPPER](playerID, params[], StringID:486("Add a speed camera"))
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
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:633("Limit of %d speed cameras reached! Increase MAX_SPEEDCAMERAS to add more speed cameras."), sizeof(speedCameras));
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