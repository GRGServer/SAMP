CheckSpeedCamera(playerID)
{
	new closestSpeedCamera = -1;
	new Float:closestObjectDistance;
	Foreach(arrayIndex, speedCameras)
	{
		if (speedCameras[arrayIndex][SPEEDCAMERA_OBJECTID] && IsValidDynamicObject(speedCameras[arrayIndex][SPEEDCAMERA_OBJECTID]))
		{
			new Float:position[3];
			GetDynamicObjectPos(speedCameras[arrayIndex][SPEEDCAMERA_OBJECTID], position[0], position[1], position[2]);
			new Float:distance = GetPlayerDistanceFromPoint(playerID, position[0], position[1], position[2]);
			if (distance < closestObjectDistance || closestSpeedCamera == -1)
			{
				closestSpeedCamera = arrayIndex;
				closestObjectDistance = distance;
			}
		}
	}

	new vehicleID = GetPlayerVehicleID(playerID);

	if (!vehicleID || closestSpeedCamera == -1 || closestObjectDistance > SPEEDCAMERA_DISTANCE)
	{
		PVar:playerID[SPEEDCAM_LIMITREACHED] = false;
		return false;
	}

	if (vehicleID && VehicleProperty:vehicleID[SPEED] > speedCameras[closestSpeedCamera][SPEEDCAMERA_SPEEDLIMIT] + SPEEDCAMERA_TOLERANCE)
	{
		if (!PVar:playerID[SPEEDCAM_LIMITREACHED])
		{
			PVar:playerID[SPEEDCAM_LIMITREACHED] = true;
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:453(""), VehicleProperty:vehicleID[SPEED], speedCameras[closestSpeedCamera][SPEEDCAMERA_SPEEDLIMIT]);
		}
	}
	else
	{
		PVar:playerID[SPEEDCAM_LIMITREACHED] = false;
	}

	return true;
}